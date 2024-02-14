<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html" encoding="UTF-8"/>

	<xsl:template match="/">
		<html>
			<head>
				<title>Tagged Text Output</title>
			</head>
			<body>
				<h1>Tagged Text Visualization</h1>
				<p>
					<xsl:for-each select="text/mot">
						<span>
							<xsl:value-of select="."/>
							<xsl:text> [</xsl:text>
							<xsl:value-of select="@categorie"/>
							<xsl:text>] </xsl:text>
						</span>
					</xsl:for-each>
				</p>
			</body>
		</html>
	</xsl:template>
</xsl:stylesheet>
