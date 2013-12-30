package net.topikachu.mixpoc;

import javax.swing.WindowConstants;

import org.mozilla.javascript.Context;
import org.mozilla.javascript.ContextFactory;
import org.mozilla.javascript.Scriptable;
import org.mozilla.javascript.ScriptableObject;
import org.mozilla.javascript.tools.debugger.Dim;
import org.mozilla.javascript.tools.debugger.ScopeProvider;
import org.mozilla.javascript.tools.debugger.SwingGui;
import org.mozilla.javascript.tools.shell.Global;



public class JSInterp {

	public static void init(String nativepath) {

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

	public static void run(NativeLib nativelib, String script) {

		try {

			boolean debug = true;
			ContextFactory factory = ContextFactory.getGlobal();
			final Global global = new Global();
			global.init(factory);
			global.setIn(System.in);
			global.setOut(System.out);
			global.setErr(System.err);

			final Dim dim = new Dim();
			dim.setScopeProvider(new ScopeProvider() {

				@Override
				public Scriptable getScope() {
					// TODO Auto-generated method stub
					return global;
				}
			});
			final SwingGui gui = new SwingGui(dim, "am");
			gui.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);
			dim.setBreakOnExceptions(true);
			dim.setBreak();
			dim.attachTo(factory);
			gui.pack();
			gui.setSize(600, 460);
			gui.setVisible(true);
			try {
				// Set version to JavaScript1.2 so that we get object-literal
				// style
				// printing instead of "[object Object]"
				Context cx = factory.enterContext();
				cx.setLanguageVersion(Context.VERSION_1_2);

				// Initialize the standard objects (Object, Function, etc.)
				// This must be done before scripts can be executed.
				Scriptable scope = cx.initStandardObjects();
				ScriptableObject.putProperty(scope, "nativelib", nativelib);
				// Now we can evaluate a script. Let's create a new object
				// using the object literal notation.
				Object result = cx.evaluateString(scope, script, "MySource", 1,
						null);

				System.out.println(String.format("script return value %s",
						result));

			} finally {
				Context.exit();
				dim.detach();
				gui.dispose();
			}

		} catch (Throwable e) {
			e.printStackTrace();
		}

	}

}
