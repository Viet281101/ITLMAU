package com.example.exercice_02

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.ImageButton

class MainActivity : AppCompatActivity() {

    private lateinit var start: Button
    private lateinit var open: Intent
    private lateinit var close: ImageButton

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        start = findViewById<Button>(R.id.button_start)
        open = Intent(this@MainActivity, Conversion::class.java)
        close = findViewById(R.id.button_deconnexion)
        buttonClick()
    }

    private fun buttonClick() {
        start.setOnClickListener {
            startActivity(open)
        }
        close.setOnClickListener {
            finish()
        }
    }

}