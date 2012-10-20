﻿package wky {		import flash.display.MovieClip;	import flash.desktop.NativeApplication;	import flash.filesystem.*;	import flash.utils.Endian;	import flash.events.MouseEvent;	import flash.events.Event;	import flash.globalization.StringTools;	import fl.controls.Label;	import flash.geom.Rectangle;	import flash.utils.Timer;	import fl.transitions.Tween;	import fl.transitions.easing.None;	import fl.transitions.TweenEvent;			public class TryClass extends MovieClip {		private const MAGIC_NUM:int = 0x19951004;		private const DATA_OFFSET:int = 100;		private const OP_CODE:Array = [0, 1, 2, 0xff]; // mov, load, drop, end		private var cycleDuration:Number = 0.2;		private var dataFile:File;		private var dataStream:FileStream;		private var param:ElevatorParameters;		private var stats:Stats;		private var cycleCnt:int;		//private var frameCnt:int;		private var elevArray:Array;		private var elevPos:Array;		private var waiting:Array;		private var wait_lbl:Array;		private var onboard:Array;		private var onboard_lbl:Array;		private var actions:Array;		private var bounds:Rectangle;		private var levelH:Number;		private var elevW:Number;		//private var pixelSpeed:Number;		//private var endFrame:Array;		//private var cycleFrames:int;		//private var movDir:Array;		private var interrupt:Boolean;		private var running:int;				public function TryClass() {			exit_btn.addEventListener(MouseEvent.CLICK, toExit);			dataFile = File.userDirectory.resolvePath("code/DAP/elevator-simulation/output");			//dataFile = File.applicationDirectory.resolvePath("output");			/*var dir:Array = File.getRootDirectories();			while (dir.length > 0){				trace("root dirs:" + dir.shift().nativePath);			}*/			if (!dataFile.exists || dataFile.isDirectory){				trace("bloody hell man, what file are you giving me?");				time_txt.text = "file does not exist";				//toExit(null);				return;			}			trace("good, file opened.");			if (!loadHeader()){				trace("plz be serious.I can't recognize this file!");				toExit(null);			}			trace("header verified.");			start_btn.addEventListener(MouseEvent.CLICK, startPlay);			loadStats();			//cycleFrames = cycleDuration * stage.frameRate;			bounds = new Rectangle(75, 50);			bounds.right = stage.stageWidth - 150;			bounds.bottom = stage.stageHeight - 30;			drawLevels();			drawElevs();			interrupt = true;			//sim();		}				private function loadStats():void{			var txt:String = "";			txt = txt.concat("平均等待时间：", stats.avg_twait, '\n');			txt = txt.concat("最长等待时间：", stats.max_twait, '\n');			txt = txt.concat("平均乘坐时间：", stats.avg_tonboard, '\n');			txt = txt.concat("最长乘坐时间：", stats.max_tonboard, '\n');			txt = txt.concat("平均运送率：", stats.avg_thput, '\n');			stats_txt.text = txt;		}				private function drawLevels():void		{			time_txt.text = "0";			levelH = bounds.height / param.levelNum;			graphics.lineStyle(2);			waiting = new Array;			wait_lbl = new Array;			var l:Label;			var h:Number;			for (var i:int = 0; i < param.levelNum; i++){				h = bounds.bottom - i * levelH;				l = new Label();				l.x = 20;				l.y = h - l.height;				l.text = "0";				addChild(l);				wait_lbl.push(l);				waiting.push(0);				graphics.moveTo(bounds.left, h);				graphics.lineTo(bounds.right, h);			}		}				private function drawElevs():void		{			elevW = bounds.width / param.elevatorNum;			elevArray = new Array;			onboard = new Array;			onboard_lbl = new Array;			actions = new Array;			elevPos = new Array;			//endFrame = new Array;			//movDir = new Array;			var e:Elevator;			var i:int;			var l:Label;			for (i = 0; i < param.elevatorNum; i++){				onboard.push(0);				e = new Elevator();				e.height = levelH;				e.width = e.height * 0.8;				e.x = bounds.left + i * elevW + (elevW - e.width) / 2;				e.y = bounds.bottom - e.height;				addChild(e);				elevArray.push(e);				l = new Label();				l.x = e.x				l.y = 25;				l.text = "0";				addChild(l);				onboard_lbl.push(l);				actions.push(new Array());				elevPos.push(0);				//endFrame.push(0);				//movDir.push(0);			}			//pixelSpeed = param.elevatorSpeed * levelH / stage.frameRate / cycleDuration;		}				private function startPlay(e:MouseEvent):void{			trace("start_btn clicked");			//frameCnt = -1;			cycleCnt = -1;			//addEventListener(Event.ENTER_FRAME, onFrame);			start_btn.removeEventListener(MouseEvent.CLICK, startPlay);			stop_btn.addEventListener(MouseEvent.CLICK, stopPlay);			interrupt = false;			mainRoutine();		}				private function stopPlay(e:MouseEvent): void		{			trace("stop_btn clicked.");			//removeEventListener(Event.ENTER_FRAME, onFrame);			stop_btn.removeEventListener(MouseEvent.CLICK, stopPlay);			resetShapes();			start_btn.addEventListener(MouseEvent.CLICK, startPlay);			dataStream.position = DATA_OFFSET;			interrupt = true;		}				private function mainRoutine() : void{			if (interrupt) return;			cycleCnt++;			time_txt.text = String(cycleCnt);			if (cycleCnt == param.simulationCycles){				stopPlay(null);				return;			}			trace("new cycle:" + time_txt.text);			addPassengers();			loadActions();			running = param.elevatorNum;			for (var i:int = 0; i < param.elevatorNum; i++)				execActions(i);		}				private function eventHandler(e:TweenEvent):void{			var id:int = elevArray.indexOf(e.currentTarget.obj);			if (execActions(id))				running--;			if (running == 0)				mainRoutine();		}				private function resetShapes()		{			var i:int;			trace("reset");			for (i = 0;i < param.levelNum; i++){				wait_lbl[i].text = "0";				waiting[i] = 0;			}			for (i = 0; i < param.elevatorNum; i++){				onboard[i] = 0;				onboard_lbl[i].text = "0";				elevArray[i].y = bounds.bottom - levelH;				elevPos[i] = 0;			}		}				private function loadHeader() :Boolean		{			dataStream = new FileStream();			dataStream.open(dataFile, FileMode.READ);			dataStream.endian = Endian.LITTLE_ENDIAN;			if (dataStream.readInt() != MAGIC_NUM)				return false;			var ver:int = dataStream.readInt();			trace("Version " + String(ver));			param = new ElevatorParameters(dataStream);			stats = new Stats(dataStream);			dataStream.position = DATA_OFFSET;			return true;		}				/*		private function sim():void{			for (cycleCnt = 0; cycleCnt < param.simulationCycles; cycleCnt++){				trace("new cycle");				time_txt.text = String(cycleCnt);				addPassengers();				loadActions();				for (var i:int = 0; i < param.elevatorNum; i ++){					while(!execActions(i)){}			}			}		}*/				/*		private function onFrame(e:Event) : void{			trace("onFrame!");			frameCnt++;			var i:int;			if (frameCnt % cycleFrames == 0){				frameCnt = 0;				cycleCnt++;				trace("new cycle");				time_txt.text = String(cycleCnt);				if (cycleCnt == param.simulationCycles){					stopPlay(null);					return;				}				addPassengers();				loadActions();				for (i = 0; i < param.elevatorNum; i++)					endFrame[i] = 0;			}			for (i = 0; i < param.elevatorNum; i++) {				if (frameCnt < endFrame[i]) {					elevArray[i].y += movDir[i] * pixelSpeed;				}				else {					execActions(i);				}			}		}*/				private function addPassengers() : void		{			//trace("cycle start pos:" + String(dataStream.position));			var cyc:int = dataStream.readInt();			if (cyc != cycleCnt){				trace("wtf, time isn't right");				toExit(null);			}			//trace("add pass start pos:" + String(dataStream.position));			for (var i:int = 0; i < param.levelNum; i++){				var val:int = dataStream.readInt();				waiting[i] += val;				wait_lbl[i].text = String(waiting[i]);			}			//trace("add pass end pos:" + String(dataStream.position));		}				private function execActions(id:int):Boolean{			var a:ElevAction = actions[id].shift();			while (a != null){				if (a.op == OP_CODE[2]){ // drop					onboard[id] -= a.dat;					onboard_lbl[id].text = String(onboard[id]);				}else if (a.op == OP_CODE[1]){ // load					onboard[id] += a.dat;					onboard_lbl[id].text = String(onboard[id]);					var l:int = elevPos[id];					waiting[l] -= a.dat;					wait_lbl[l].text = String(waiting[l]);				}else if (a.op == OP_CODE[0]){ // move					var yfrom:Number = elevArray[id].y;					var yto:Number = yfrom - a.dat * levelH;					//var movframe:int =  Math.abs(a.dat) * cycleDuration / param.elevatorSpeed - 1;					var execTime:Number = Math.abs(a.dat) * cycleDuration / param.elevatorSpeed;					var mov:Tween = new Tween(elevArray[id], "y", None.easeNone, yfrom, yto, execTime, true);					mov.addEventListener(TweenEvent.MOTION_FINISH, eventHandler);					//endFrame[id] += levelH * Math.abs(a.dat) / pixelSpeed;					elevPos[id] += a.dat;					//if (a.dat > 0) movDir[id] = -1;					//else movDir[id] = 1;					break;				}				a = actions[id].shift();			}			if (a == null) return true;			else return false;		}				private function loadActions() : void		{			//trace("op start pos:" + String(dataStream.position));			var op:int = dataStream.readInt();			var id:int;			var val:int;			while (op != OP_CODE[3]){				id = dataStream.readInt();				val = dataStream.readInt();				var action:ElevAction = new ElevAction();				action.op = op;				action.dat = val;				actions[id].push(action);				//trace("op start pos:" + String(dataStream.position));				op = dataStream.readInt();			}		}				private function toExit(e:MouseEvent):void 		{			trace("off we go!");			dataStream.close();			NativeApplication.nativeApplication.exit();		}			}	}