package com.megvii.guoyizhe.jnisamples;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.util.Log;
import android.widget.TextView;

import java.lang.reflect.Method;

/**
 * Created by guoyizhe on 2017/10/20.
 */

public class LessonActivity extends Activity implements ITest {

    private static final String TAG = LessonActivity.class.getName();

    static {
        System.loadLibrary("native-lib");
    }

    public static native String LessonOne();

    public static native String LessonTwo(String origin);

    public static native int[][] LessonThree(int size);

    public static native char[] LessonFour(char[] origin);

    public static native void InterfaceTest(ITest test);

    public static native void ThreadTest(LessonActivity cls);

    public static void getFromJNI(int i){

        Log.v(TAG,i + "");
    }


    private TextView tv_text;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_lesson);
        tv_text = findViewById(R.id.txt_text);
        Intent intent = getIntent();
        switch (intent.getExtras().getInt("pos")) {
            case 0:
                tv_text.setText(LessonOne());
                break;
            case 1:
                LessonTwo("testString");
                break;
            case 2:
                LessonThree(5);
                break;
            case 3:
                System.out.println(LessonFour(new char[]{'3', '5'}));
                break;
            case 4:
                InterfaceTest(this);
                break;
            case 5:
                ThreadTest(LessonActivity.this);
            default:
                break;
        }

        try {
            Class cls = Class.forName("com.megvii.guoyizhe.jnisamples.LessonActivity");
            Method method = cls.getMethod("getFromJNI", int.class);
        } catch (ClassNotFoundException e) {
            System.out.println("class not found");
            e.printStackTrace();
        } catch (NoSuchMethodException e) {
            System.out.println("no such method");
            e.printStackTrace();
        }
    }

    @Override
    public void getInfo(String txt) {
        tv_text.setText("text from interface callback" + txt);
    }
}
