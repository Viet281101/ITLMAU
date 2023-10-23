package com.example.exemple_04_v1

import android.content.SharedPreferences
import android.content.SharedPreferences.Editor
import android.graphics.Color
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.TypedValue
import android.widget.EditText
import android.widget.RadioGroup
import android.widget.Switch
import kotlin.properties.Delegates

class MainActivity : AppCompatActivity() {
    private lateinit var text: EditText// le texte

    private lateinit var size: RadioGroup// la taille
    private var textSize by Delegates.notNull<Float>()

    private lateinit var contrast: Switch// le contraste
    private var textColor by Delegates.notNull<Int>()
    private var backgroundTextColor by Delegates.notNull<Int>()

    private lateinit var sharedPreferences: SharedPreferences// enregistrer
    private lateinit var editor: Editor
    

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        this.text = findViewById(R.id.text)// le texte

        this.size = findViewById(R.id.size_choices)// la taille
        this.textSize = 10F
        toSize()

        this.contrast = findViewById(R.id.contrast_choices)// le contraste
        this.textColor = Color.BLACK
        this.backgroundTextColor = Color.WHITE
        toContrast()

        this.sharedPreferences = getSharedPreferences("Preferences", MODE_PRIVATE)// enregistrer
        this.editor = this.sharedPreferences.edit()
        toLoad()

    }

    private fun toSize() {// la taille
        this.size.setOnCheckedChangeListener { radioGroup, i ->
            if (i == R.id.size_10) {
                this.textSize = 10F
            } else if (i == R.id.size_20) {
                this.textSize = 20F
            } else if (i == R.id.size_30) {
                this.textSize = 30F
            }
            this.text.setTextSize(TypedValue.COMPLEX_UNIT_PT, this.textSize)
            this.editor.apply {
                putInt("Taille", size.getCheckedRadioButtonId())
                putFloat("TailleTexte", textSize)
            }.apply()
        }
    }

    private fun toContrast() {// le contraste
        this.contrast.setOnCheckedChangeListener { compoundButton, b ->
            if (b) {
                this.textColor = Color.WHITE
                this.backgroundTextColor = Color.BLACK
            } else {
                this.textColor = Color.BLACK
                this.backgroundTextColor = Color.WHITE
            }
            this.text.setTextColor(this.textColor)
            this.text.setBackgroundColor(this.backgroundTextColor)
            this.editor.apply {
                putBoolean("Contraste", contrast.isChecked)
                putInt("CouleurTexte", textColor)
                putInt("CouleurEditeurTexte", backgroundTextColor)
            }.apply()
        }
    }

    private fun toLoad() {// charger ce qui est enregistré
        this.size.check(this.sharedPreferences.getInt("Taille", R.id.size_10))// la taille
        this.text.setTextSize(TypedValue.COMPLEX_UNIT_PT, this.sharedPreferences.getFloat("TailleTexte", this.textSize))

        this.contrast.isChecked = this.sharedPreferences.getBoolean("Contraste", false)// le contraste
        this.text.setTextColor(this.sharedPreferences.getInt("CouleurTexte", this.textColor))
        this.text.setBackgroundColor(this.sharedPreferences.getInt("CouleurEditeurTexte", this.backgroundTextColor))
    }

}
