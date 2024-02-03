<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:template match="/">
		<html>
		<body>
			<h1 style="color: blue;" align="center">My Magic Spell Circles Collection</h1>
			<br/>
			<table border="2" align="center" bgcolor="grey">
				<tr bgcolor="#639bff" style="color: cyan;">
					<th>Order</th>
					<th>Spell</th>
					<th>Name</th>
					<th>Type</th>
					<th colspan="4">Damage Points</th>
					<th colspan="2">Type Chart</th>
					<th>Descriptions</th>
				</tr>
				<tr bgcolor="#639bff" style="color: cyan;">
					<th colspan="4"></th>
					<th>Physical</th>
					<th>Mana</th>
					<th>Critical</th>
					<th>Vulnerable</th>
					<th>To</th>
					<th>By</th>
					<th></th>
				</tr>

				<xsl:for-each select="magic_circle/spell_circle">
					<tr>
						<td style="color: black;"><xsl:apply-templates select="nbr_order"/></td>
						<td style="color: black;"><xsl:apply-templates select="image"/></td>
						<td style="color: black;"><xsl:value-of select="name"/></td>
						<td align="center" style="color: black;">
							<xsl:for-each select="types/type">
								<xsl:sort select="@number" order="descending"/>
								<br/>
								<xsl:value-of select="."/>
								<br/>
							</xsl:for-each>
						</td>
						<td align="center" style="color: black;"><xsl:value-of select="damages/physical_damage"/></td>
						<td align="center" style="color: black;"><xsl:value-of select="damages/magic_damage"/></td>
						<td align="center" style="color: black;"><xsl:value-of select="damages/critical_damage"/></td>
						<td align="center" style="color: black;"><xsl:value-of select="damages/effective_damage"/></td>
						<td align="center" style="color: black;">
							<xsl:for-each select="type_chart/type_advantage">
								<xsl:value-of select="."/>
								<br/>
							</xsl:for-each>
						</td>
						<td align="center" style="color: black;">
							<xsl:for-each select="type_chart/vulnerable_to">
								<xsl:value-of select="."/>
								<br/>
							</xsl:for-each>
						</td>
						<td align="left" style="color: black;"><xsl:value-of select="descriptions"/></td>
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