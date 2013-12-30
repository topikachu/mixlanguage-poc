package net.topikachu.mixpoc;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.ContextFactory;
import org.mozilla.javascript.Function;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.ScriptableObject;
import org.mozilla.javascript.tools.debugger.Main;
import org.mozilla.javascript.tools.debugger.ScopeProvider;

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

	// public static void run(String script) {
	// try {
	// System.out.println(String.format("the script is %s\n", script));
	// ScriptEngineManager mgr = new ScriptEngineManager();
	// ScriptEngine engine = mgr.getEngineByName("JavaScript");
	// engine.put("nativelib", NATIVE_LIB_INSTANCE);
	// System.out.println(String.format("script return value %s",engine.eval(script)));
	// } catch (Throwable e) {
	// e.printStackTrace();
	// }
	// }
	//

	public static void run(String script) {
	
		try {
			boolean debug = true;
			ContextFactory ctxFac;

			if (debug) {
				ctxFac = org.mozilla.javascript.tools.shell.Main.shellContextFactory;
				Main.mainEmbedded(ctxFac, new ScopeProvider() {
					public Scriptable getScope() {
						return org.mozilla.javascript.tools.shell.Main
								.getGlobal();
					}
				}, "Taglib JavaScript");
			} else {
				ctxFac = Context.enter().getFactory();
			}

			Context cx = ctxFac.enterContext();
			try {
				// Set version to JavaScript1.2 so that we get object-literal
				// style
				// printing instead of "[object Object]"
				cx.setLanguageVersion(Context.VERSION_1_2);

				// Initialize the standard objects (Object, Function, etc.)
				// This must be done before scripts can be executed.
				Scriptable scope = cx.initStandardObjects();
				ScriptableObject.putProperty(scope, "nativelib", NATIVE_LIB_INSTANCE);
				// Now we can evaluate a script. Let's create a new object
				// using the object literal notation.
				Object result = cx.evaluateString(scope, script, "MySource",
						1, null);

				System.out.println(String.format("script return value %s",
						result));
			} finally {
				Context.exit();
			}

		} catch (Throwable e) {
			e.printStackTrace();
		}

	}
}
