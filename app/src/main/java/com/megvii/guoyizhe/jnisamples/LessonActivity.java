package com.megvii.guoyizhe.jnisamples;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.widget.TextView;

/**
 * Created by guoyizhe on 2017/10/20.
 */

public class LessonActivity extends Activity implements ITest{

    static {
        System.loadLibrary("native-lib");
    }

    public static native String LessonOne();

    public static native String LessonTwo(String origin);

    public static native int[][] LessonThree(int size);

    public static native char[] LessonFour(char[] origin);

    public static native void InterfaceTest(ITest test);


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
                System.out.println(LessonFour(new char[]{'3','5'}));
                break;
            case 4:
                InterfaceTest(this);
                break;
            default:
                break;
        }
    }

    @Override
    public void getInfo(String txt) {
        System.out.println(txt);
    }
}
