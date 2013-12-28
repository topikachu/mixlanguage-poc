package net.topikachu.mixpoc;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;

import com.sun.jna.Native;

public class JSInterp {
	static NativeLib NATIVE_LIB_INSTANCE;

	public static void init(String nativepath) {
		try {
		NATIVE_LIB_INSTANCE = (NativeLib) Native.loadLibrary(nativepath,
				NativeLib.class);
		} catch (Throwable e) {
			e.printStackTrace();
		}
	}

	public static void run(String script) {
		try {
			System.out.println(String.format("the script is %s\n", script));
			ScriptEngineManager mgr = new ScriptEngineManager();
			ScriptEngine engine = mgr.getEngineByName("JavaScript");
			engine.put("nativelib", NATIVE_LIB_INSTANCE);
			System.out.println(String.format("script return value %s",engine.eval(script)));
		} catch (Throwable e) {
			e.printStackTrace();
		}
	}
}
