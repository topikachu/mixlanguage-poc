package net.topikachu.mixpoc;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;

import com.sun.jna.Native;

public class JSInterp {
	static NativeLib LIB_INSTANCE;

	public static void init(String nativepath) {
		LIB_INSTANCE = (NativeLib) Native.loadLibrary(nativepath,
				NativeLib.class);
	}

	public static void run(String script) {
		try {
			System.out.println(script);
			ScriptEngineManager mgr = new ScriptEngineManager();
			ScriptEngine engine = mgr.getEngineByName("JavaScript");
			engine.put("lib", LIB_INSTANCE);
			System.out.println(engine.eval(script));
		} catch (Throwable e) {
			e.printStackTrace();
		}
	}
}
