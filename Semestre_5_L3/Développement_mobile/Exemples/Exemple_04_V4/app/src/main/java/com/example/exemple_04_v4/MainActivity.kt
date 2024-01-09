package com.example.exemple_04_v4

import android.content.SharedPreferences
import android.content.SharedPreferences.Editor
import android.graphics.Color
import android.graphics.Typeface
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.TypedValue
import android.widget.Button
import android.widget.EditText
import android.widget.RadioGroup
import android.widget.Switch
import kotlin.properties.Delegates

class MainActivity : AppCompatActivity() {

    private lateinit var text: EditText
    private lateinit var size: RadioGroup
    private lateinit var contrast: Switch
    private lateinit var sharedPreferences: SharedPreferences
    private lateinit var editor: Editor
    private var textColor by Delegates.notNull<Int>()
    private var backgroundTextColor by Delegates.notNull<Int>()
    private var textSize by Delegates.notNull<Float>()
    private lateinit var styles: Array<Int>
    private lateinit var styles_buttons: Array<Button>

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Variables déclarations
        this.text = findViewById(R.id.text)
        this.size = findViewById(R.id.size_choices)
        this.contrast = findViewById(R.id.contrast_choices)
        this.sharedPreferences = getSharedPreferences("Preferences", MODE_PRIVATE)
        this.editor = this.sharedPreferences.edit()
        this.textSize = 10F
        this.textColor = Color.BLACK
        this.backgroundTextColor = Color.WHITE
        this.styles_buttons = arrayOf(findViewById(R.id.style_normal), findViewById(R.id.style_bold), findViewById(R.id.style_italic))
        this.styles = arrayOf(Typeface.NORMAL, Typeface.BOLD, Typeface.ITALIC)

        toLoad()
        toSize()
        toContrast()
        toStyle()

    }

    private fun toLoad() {
        this.size.check(this.sharedPreferences.getInt("Taille", R.id.size_10))
        this.contrast.isChecked = this.sharedPreferences.getBoolean("Contraste", false)
        this.styles_buttons[this.sharedPreferences.getInt("Style", 0)].setBackgroundColor(Color.BLACK)
        this.text.setTextSize(TypedValue.COMPLEX_UNIT_PT, this.sharedPreferences.getFloat("TailleTexte", this.textSize))
        this.text.setTextColor(this.sharedPreferences.getInt("CouleurTexte", this.textColor))
        this.text.setBackgroundColor(this.sharedPreferences.getInt("CouleurEditeurTexte", this.backgroundTextColor))
        this.text.setTypeface(null, this.styles[this.sharedPreferences.getInt("Style", 0)])
    }

    private fun toSize() {
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

    private fun toContrast() {
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

    private fun toStyle(){
        for(j in 0 until 3) {
            this.styles_buttons[j].setOnClickListener {
                this.text.setTypeface(null, this.styles[j])
                for (i in 0 until 3) {
                    if (j == i) {
                        this.styles_buttons[i].setBackgroundColor(Color.BLACK)
                    } else {
                        this.styles_buttons[i].setBackgroundColor(Color.TRANSPARENT)
                    }
                }
                this.editor.apply {
                    putInt("Style", j)
                }.apply()
            }
        }
    }

}