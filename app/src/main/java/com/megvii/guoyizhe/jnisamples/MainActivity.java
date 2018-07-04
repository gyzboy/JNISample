package com.megvii.guoyizhe.jnisamples;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.RecyclerView.ViewHolder;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    RecyclerView rv_list;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        rv_list = (RecyclerView) findViewById(R.id.rv_list);
        LinearLayoutManager llm = new LinearLayoutManager(MainActivity.this);
        rv_list.setLayoutManager(llm);
        ArrayList<String> list = new ArrayList<>();
        list.add("JNI Lesson1");
        list.add("JNI Lesson2");
        list.add("JNI Lesson3");
        list.add("JNI Lesson4");
        list.add("JNI Lesson5");
        list.add("JNI Lesson6");
        list.add("JNI Lesson Nio");
        CustomAdapter adapter = new CustomAdapter(list);
        rv_list.setAdapter(adapter);

    }

    public native String stringFromJNI();

    public native String sayHello();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    class CustomAdapter extends RecyclerView.Adapter<CustomAdapter.CustomHolder> {

        private ArrayList<String> list;
        private CustomHolder holder;

        public CustomAdapter(ArrayList<String> datas) {
            list = datas;
        }

        @Override
        public CustomHolder onCreateViewHolder(ViewGroup parent, int viewType) {
            View view = View.inflate(MainActivity.this,R.layout.item_text,null);
            holder = new CustomHolder(view);
            return holder;
        }

        @Override
        public void onBindViewHolder(CustomHolder holder, int position) {
            holder.mButton.setText(list.get(position));
        }

        @Override
        public int getItemCount() {
            return list.size();
        }

        class CustomHolder extends ViewHolder {

            public Button mButton;

            public CustomHolder(final View itemView) {
                super(itemView);
                mButton =  itemView.findViewById(R.id.btn_info);
                mButton.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        startActivity(new Intent(MainActivity.this,LessonActivity.class).putExtra("pos",getLayoutPosition()));
                    }
                });
            }
        }
    }
}