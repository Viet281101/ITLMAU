<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html" encoding="UTF-8"/>

	<xsl:template match="/">
		<html>
		<head>
			<title>Conte Transformé</title>
		</head>
		<body>
			<h1>Texte du Conte</h1>
			<xsl:for-each select="text/sentence">
				<div style="margin-bottom: 20px;">
					<h2>Sentence <xsl:value-of select="@id"/></h2>
					<p><xsl:value-of select="."/></p>
				</div>
			</xsl:for-each>
		</body>
		</html>
	</xsl:template>
</xsl:stylesheet>
