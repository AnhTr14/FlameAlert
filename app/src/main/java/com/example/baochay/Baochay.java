package com.example.baochay;

public class Baochay {
    public String Nhietdo;
    public String Nongdokk;
    public String Tialua;

    public Baochay(String nhietdo, String nongdokk, String tialua) {
        Nhietdo = nhietdo;
        Nongdokk = nongdokk;
        Tialua = tialua;
    }

    public String getNhietdo() {
        return Nhietdo;
    }

    public void setNhietdo(String nhietdo) {
        Nhietdo = nhietdo;
    }

    public String getNongdokk() {
        return Nongdokk;
    }

    public void setNongdokk(String nongdokk) {
        Nongdokk = nongdokk;
    }

    public String getTialua() {
        return Tialua;
    }

    public void setTialua(String tialua) {
        Tialua = tialua;
    }
}
