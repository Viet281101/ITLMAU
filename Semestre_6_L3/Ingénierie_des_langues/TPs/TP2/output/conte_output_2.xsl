<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html"/>
    <xsl:template match="/">
        <html>
        <head><title>Conte</title></head>
        <body>
            <xsl:for-each select="text/sentence">
                <div>
                    <h2>Sentence <xsl:value-of select="@id"/></h2>
                    <p>
                        <xsl:for-each select="mot">
                            <xsl:value-of select="."/>
                            <xsl:if test="position()!=last()"> </xsl:if>
                        </xsl:for-each>
                    </p>
                </div>
            </xsl:for-each>
        </body>
        </html>
    </xsl:template>
</xsl:stylesheet>
