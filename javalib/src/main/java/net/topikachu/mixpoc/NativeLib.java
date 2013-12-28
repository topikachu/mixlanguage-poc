package net.topikachu.mixpoc;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface NativeLib extends Library {

 int nativeadd(int a,int b);
}