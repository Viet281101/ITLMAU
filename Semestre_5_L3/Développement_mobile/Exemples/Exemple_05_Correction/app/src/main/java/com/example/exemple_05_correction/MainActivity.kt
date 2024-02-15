package com.example.exemple_05_correction

import android.content.Context
import android.os.Bundle
import android.os.Environment
import android.widget.EditText
import android.widget.ImageButton
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import java.io.BufferedReader
import java.io.File
import java.io.FileInputStream
import java.io.FileNotFoundException
import java.io.FileOutputStream
import java.io.InputStreamReader

class MainActivity : AppCompatActivity() {

	private lateinit var title: EditText
	private lateinit var text: EditText
	private lateinit var save: ImageButton
	private lateinit var open: ImageButton
	private lateinit var delete: ImageButton
	private lateinit var disconect: ImageButton
	private lateinit var file: String
	private lateinit var data: String

	override fun onCreate(savedInstanceState: Bundle?) {
		super.onCreate(savedInstanceState)
		setContentView(R.layout.activity_main)

		initiate()
		toClick()
	}

	private fun initiate(){
		this.title = findViewById(R.id.text_title)
		this.text = findViewById(R.id.text)
		this.save = findViewById(R.id.text_save)
		this.open = findViewById(R.id.text_open)
		this.delete = findViewById(R.id.text_delete)
		this.disconect = findViewById(R.id.disconnect)
	}

	private fun toClick(){
		this.save.setOnClickListener {
			toSave() // sauvegarder dans la mémoire interne
			/*if(isExternalStorageWritable()){ //sauvegarder dans la mémoire externe
				toExternalSave()
			}else{
				Toast.makeText(this, "Vous n'avez pas d'espace de stockage externe!", Toast.LENGTH_SHORT).show()
			}*/
		}
		this.open.setOnClickListener {
			toOpen()
		}
		this.delete.setOnClickListener {
			toDelete()
		}
		this.disconect.setOnClickListener {
			finish()
		}
	}

	private fun toSave(){
		this.file = this.title.text.toString()
		this.data = this.text.text.toString()
		val fileOutputStream: FileOutputStream
		try {
			fileOutputStream = openFileOutput(this.file, Context.MODE_PRIVATE)
			fileOutputStream.write(this.data.toByteArray())
		}
		catch(e: FileNotFoundException){
			e.printStackTrace()
		}
		catch (e: Exception){
			e.printStackTrace()
		}
	}

	private fun toOpen(){

		this.file = this.title.text.toString()

		if(this.file.trim()!=""){
			try {
				var fileInputStream: FileInputStream? = null
				fileInputStream = openFileInput(this.file)

				var inputStreamReader: InputStreamReader
				inputStreamReader = InputStreamReader(fileInputStream)

				val bufferedReader: BufferedReader
				bufferedReader = BufferedReader(inputStreamReader)

				var stringBuilder: StringBuilder = StringBuilder()
				var text: String? = null

				while ({ text = bufferedReader.readLine(); text }() != null) {
					stringBuilder.append(text)
				}

				this.text.setText(stringBuilder).toString()

			}catch (e: FileNotFoundException){

				e.printStackTrace()
				Toast.makeText(this, "Ce fichier n'existe pas!", Toast.LENGTH_SHORT).show()

			}catch (e: Exception){

				e.printStackTrace()

			}
		}else{

			Toast.makeText(this, "Choisir un nom de fichier!", Toast.LENGTH_SHORT).show()

		}
	}

	private fun toDelete(){

		this.file = this.title.text.toString()

		if(this.file.trim()!="") {

			try{

				deleteFile(this.file)

			}catch (e: FileNotFoundException){
				e.printStackTrace()
				Toast.makeText(this, "Ce fichier n'existe pas!", Toast.LENGTH_SHORT).show()
			}catch (e: Exception){
				e.printStackTrace()
			}

		}else{

			Toast.makeText(this, "Choisir un fichier à supprimer!", Toast.LENGTH_SHORT).show()

		}
	}

	private fun isExternalStorageWritable(): Boolean {
		return Environment.getExternalStorageState() == Environment.MEDIA_MOUNTED
	}

	private fun toExternalSave(){
		this.file = this.title.text.toString()
		val externalFile = File(this.getExternalFilesDir(null), this.file)
		externalFile.createNewFile()
		externalFile.writeBytes(this.text.text.toString().toByteArray())
	}

}