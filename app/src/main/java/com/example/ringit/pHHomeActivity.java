package com.example.ringit;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.util.Map;

public class pHHomeActivity extends AppCompatActivity {

    private TextView pHValueShow;
    private Button LogoutBtn;
    DatabaseReference pHReference;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_p_h_home);

        pHValueShow = (TextView) findViewById(R.id.pHvalue_show);
        LogoutBtn = (Button) findViewById(R.id.logout_btn);

        pHReference = FirebaseDatabase.getInstance().getReference();
        pHReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {

                String pH = dataSnapshot.child("pH").getValue().toString();
                pHValueShow.setText(pH);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

        LogoutBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent(pHHomeActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });

    }
}
