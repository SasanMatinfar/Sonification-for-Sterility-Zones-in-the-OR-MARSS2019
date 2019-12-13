(
~musicBuffer1 = Buffer.read(s, '/Users/shervindehghani/Desktop/team16/data/audio/autumnleaves.wav');
~musicBuffer2 = Buffer.read(s, '/Users/shervindehghani/Desktop/team16/data/audio/englishman.wav');
~musicBuffer3 = Buffer.read(s, '/Users/shervindehghani/Desktop/team16/data/audio/montypython.wav');

~splashBuffer = Buffer.read(s, '/Users/shervindehghani/Desktop/team16/data/audio/splash.wav');
~rainBuffer = Buffer.read(s, '/Users/shervindehghani/Desktop/team16/data/audio/rain.wav');

SynthDef.new("player", {
	arg rate=1, amp=0.5, start, loop=0, buf, end, out=0, freq=440, rq=1, mul=1, add=0, lgrt=2;
	var sig, ptr;

	sig = PlayBuf.ar(2, buf, rate.lag(lgrt)*BufRateScale.kr(buf), 1.0, start, 0.0, loop, 2);
	sig = BPF.ar(sig, freq, rq, mul, add);
	sig = sig * amp;

	Out.ar(out, sig);
}).add;

SynthDef.new("reverb", {
	arg in, predelay=0.1, revtime=1.8,
	lpf=4500, mix=0.15, amp=1, out=0;
	var dry, wet, temp, sig;
	dry = In.ar(in,2);
	temp = In.ar(in,2);
	wet = 0;
	temp = DelayN.ar(temp, 0,2, predelay);
	16.do{
		temp = AllpassN.ar(temp, 0.05, {Rand(0.001,0.05)}!2, revtime);
		temp = LPF.ar(temp, lpf);
		wet = wet + temp;
	};
	sig = XFade2.ar(dry, wet, mix*2-1, amp);
	Out.ar(out, sig);
}).add;


OSCdef.new(\start,{
	arg msg;
	msg.postln;

	x = Synth.new("reverb", [
		\in, 4,
		\out, 0]);


	if(msg[1] == 1)
	{
			msg.postln;
			msg.postln;
		y = Synth.new("player", [\buf, ~musicBuffer1.bufnum,
		\out, 4,
		\start, 0,
		\end, ~musicBuffer1.numFrames,
		\amp, 0.5]);
	};
	if(msg[1] == 2)
	{
			msg.postln;
			msg.postln;

		y = Synth.new("player", [\buf, ~musicBuffer2.bufnum,
		\out, 4,
		\start, 0,
		\end, ~musicBuffer2.numFrames,
		\amp, 0.5]);
	};
		if(msg[1] == 3)
	{
			msg.postln;
			msg.postln;
			y = Synth.new("player", [\buf, ~musicBuffer3.bufnum,
		\out, 4,
		\start, 0,
		\end, ~musicBuffer3.numFrames,
		\amp, 0.5]);
	};

},
'/root/start'
);


OSCdef.new(\do,
	{
		arg msg;
		msg.postln;

		y.set(\freq, 100, \rq, 1);
		x.set(\predelay, 15);

		z = Synth.new("player", [\buf, ~splashBuffer.bufnum,
			\out, 0,
			\start, 0,
			\end, ~splashBuffer.numFrames,
			\amp, 1,
			\loop, 0.0]);
	},
	'/root/enter_negative_plane'
);

OSCdef.new(\undo,
	{
		arg msg;
		msg.postln;

		y.set(\freq, 440, \rq, 0.5);
		x.set(\predelay, 0.0);
	},
	'/root/enter_positive_plane'
);

OSCdef.new(\dorain,
	{
		arg msg;
		msg.postln;

		~wave = Synth.new("player", [\buf, ~rainBuffer.bufnum,
			\out, 0,
			\start, 0,
			\end, ~rainBuffer.numFrames,
			\amp, 1,
			\loop, 1.0]);
	},
	'/root/enter_negative_sphere'
);

OSCdef.new(\stoprain,
	{
		arg msg;
		msg.postln;

		~wave.set(\amp, 0);

	},
	'/root/enter_positive_sphere'
);

OSCdef.new(\stop,
	{
		arg msg;
		msg.postln;
	},
	'/root/stop'
);
)






