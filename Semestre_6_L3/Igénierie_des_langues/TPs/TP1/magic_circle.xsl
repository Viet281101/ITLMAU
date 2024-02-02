<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:template match="/">
		<html>
		<body>
			<h1 style="color: cyan;" align="center">My Magic Spell Circles Collection</h1>
			<br/>
			<table border="2" align="center">
				<tr bgcolor="#639bff" style="color: cyan;">
					<th>List</th>
					<th>Spell</th>
					<th>Name</th>
					<th>Type</th>
					<th colspan="4">Damage Points</th>
					<th>Type Chart</th>
					<th>Descriptions</th>
				</tr>
				<tr bgcolor="#639bff" style="color: cyan;">
					<th colspan="4"></th>
					<th>Physical Damage</th>
					<th>Mana Damage</th>
					<th>Critical Damage</th>
					<th>Vulnerable Damage</th>
					<th colspan="2"></th>
				</tr>

				<xsl:for-each select="magic_circle/spell_circle">
					<tr>
						<td><xsl:apply-templates select="nbr_order"/></td>
						<td><xsl:apply-templates select="image"/></td>
						<td><xsl:value-of select="name"/></td>
						<td align="center">
							<xsl:for-each select="types/type">
								<xsl:sort select="type" order="descending"/>
								<br/>
								<xsl:value-of select="."/>
								<br/>
							</xsl:for-each>
						</td>
						<td align="center"><xsl:value-of select="damages/physical_damage"/></td>
						<td align="center"><xsl:value-of select="damages/magic_damage"/></td>
						<td align="center"><xsl:value-of select="damages/critical_damage"/></td>
						<td align="center"><xsl:value-of select="damages/effective_damage"/></td>
						<td></td>
						<td></td>
					</tr>
				</xsl:for-each>
			</table>
			<br/><br/>
		</body>
		</html>
	</xsl:template>

	<xsl:template match="image">
		<img src="{@url}" width="150"/>
	</xsl:template>

</xsl:stylesheet> 