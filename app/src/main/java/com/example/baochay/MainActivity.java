package com.example.baochay;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    TextView tvNhietdo, tvNongdokk, tvTialua,tvTinhtrangchay;
    Button btnTatchuong;
    Float Chuong;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        tvNhietdo=(TextView) findViewById(R.id.tv_nhietdo);
        tvNongdokk=(TextView) findViewById(R.id.tv_nongdokk);
        tvTialua=(TextView) findViewById(R.id.tv_tialua);
        tvTinhtrangchay=(TextView) findViewById(R.id.tv_tinhtrang);
        btnTatchuong=(Button)findViewById(R.id.btn_chuong);
        //
        FirebaseDatabase firebaseDatabase = FirebaseDatabase.getInstance();
        DatabaseReference databaseReference = firebaseDatabase.getReference();

        databaseReference.child("Baochay/KhongKhi").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                Float khongkhi = snapshot.getValue(Float.class);
                tvNongdokk.setText(khongkhi.toString()+" ppm");
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
        databaseReference.child("Baochay/NhietDo").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                Float nhietdo = snapshot.getValue(Float.class);
                tvNhietdo.setText(nhietdo.toString() +" độ C");

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
        databaseReference.child("Baochay/TiaLua").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                Float tialua = snapshot.getValue(Float.class);
                if(tialua==1)
                {
                    tvTialua.setText("Có Lửa");
                }
                else
                {
                    tvTialua.setText("Không có Lửa");
                }

            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
        databaseReference.child("Baochay/TinhTrangChay").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                Float tinhtrangchay = snapshot.getValue(Float.class);
                if (tinhtrangchay==1) {
                    tvTinhtrangchay.setText("Báo cháy");
                    btnTatchuong.setVisibility(View.VISIBLE);
                    tvTinhtrangchay.setBackgroundColor(Color.parseColor("#FF3333"));

                }
                else {
                    tvTinhtrangchay.setText("Bình thường");
                    btnTatchuong.setVisibility(View.INVISIBLE);
                    tvTinhtrangchay.setBackgroundColor(Color.parseColor("#00CC66"));

                }
            }
            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

    }
}