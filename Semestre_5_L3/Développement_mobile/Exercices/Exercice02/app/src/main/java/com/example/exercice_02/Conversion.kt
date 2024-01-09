package com.example.exercice_02

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import android.widget.ImageButton
import android.widget.Toast
import kotlin.math.pow

class Conversion : AppCompatActivity() {

    private lateinit var decimal: EditText
    private lateinit var binary: EditText
    private lateinit var towardDecimal: ImageButton
    private lateinit var towardBinary: ImageButton
    private lateinit var towardBack: ImageButton

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_conversion)
        decimal = findViewById(R.id.numberDecimal)
        binary = findViewById(R.id.numberBinary)
        towardDecimal = findViewById(R.id.button_towardDecimal)
        towardBinary = findViewById(R.id.button_towardBinary)
        towardBack = findViewById(R.id.button_back)
        buttonClick()
    }

    private fun buttonClick(){ // Instantiation des boutons et de leurs méthodes
        towardBinary.setOnClickListener {
            convertToBinary()
        }
        towardDecimal.setOnClickListener {
            convertToDecimal()
        }
        towardBack.setOnClickListener{
            finish()
        }
    }

    private fun convertToBinary(){//Vérifier valeur décimal - entière
        if (decimal.text.isEmpty()) {
            Toast.makeText(this, "Pas de valeur décimale à convertir!", Toast.LENGTH_SHORT).show()
        }
        else{
            binary.setText(euclideanConversion(decimal.text.toString()))
        }
    }

    private fun convertToDecimal(){//Vérifier valeur binaire
        val laList = binary.text.toString().toList()
        val newList = arrayListOf<Int>()
        var check = true
        var number : Int

        if (binary.text.isEmpty()) {
            Toast.makeText(this, "Pas de valeur binaire à convertir!", Toast.LENGTH_SHORT).show()
        }
        else{
            for (char in laList){
                number = char.toString().toInt()
                if (number == 0 || number == 1) {
                    newList.add(number)
                }
                else{
                    check = false
                }
            }
            if(check){
                decimal.setText(conversionInverse(newList))
            }
            else{
                Toast.makeText(this, "Pas de valeur binaire à convertir!", Toast.LENGTH_SHORT).show()
            }
        }
    }

    private fun euclideanConversion(decimalValue: String): String {
        var list = ""
        var value = decimalValue.toLong()
        while(value != 0L){
            if(value%2 == 0L){
                value /= 2
                list += "0"
            }
            else{
                value -= 1
                value /= 2
                list += "1"
            }
        }
        return list.reversed()
    }

    private fun conversionInverse(list: List<Int>): String {
        var value = 0.0
        var compteur = list.size.toDouble()
        for(number in list){
            compteur -= 1
            value += number* 2.0.pow(compteur)
        }
        return value.toLong().toString()
    }
}