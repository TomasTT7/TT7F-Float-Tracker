<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.4.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="50" name="dxf" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="14" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="14" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="1" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="7" fill="1" visible="no" active="no"/>
<layer number="56" name="wert" color="7" fill="1" visible="no" active="no"/>
<layer number="57" name="tCAD" color="7" fill="1" visible="no" active="no"/>
<layer number="59" name="tCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="60" name="bCarbon" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="7" fill="1" visible="yes" active="yes"/>
<layer number="100" name="Muster" color="7" fill="1" visible="yes" active="yes"/>
<layer number="101" name="Patch_Top" color="7" fill="1" visible="yes" active="yes"/>
<layer number="102" name="Vscore" color="7" fill="1" visible="yes" active="yes"/>
<layer number="103" name="tMap" color="7" fill="1" visible="yes" active="yes"/>
<layer number="104" name="Name" color="7" fill="1" visible="yes" active="yes"/>
<layer number="105" name="tPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="106" name="bPlate" color="7" fill="1" visible="yes" active="yes"/>
<layer number="107" name="Crop" color="7" fill="1" visible="yes" active="yes"/>
<layer number="108" name="fp8" color="7" fill="1" visible="yes" active="yes"/>
<layer number="109" name="fp9" color="7" fill="1" visible="yes" active="yes"/>
<layer number="110" name="fp0" color="7" fill="1" visible="yes" active="yes"/>
<layer number="111" name="LPC17xx" color="7" fill="1" visible="yes" active="yes"/>
<layer number="112" name="tSilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="113" name="IDFDebug" color="7" fill="1" visible="yes" active="yes"/>
<layer number="114" name="Badge_Outline" color="7" fill="1" visible="yes" active="yes"/>
<layer number="115" name="ReferenceISLANDS" color="7" fill="1" visible="yes" active="yes"/>
<layer number="116" name="Patch_BOT" color="7" fill="1" visible="yes" active="yes"/>
<layer number="118" name="Rect_Pads" color="7" fill="1" visible="yes" active="yes"/>
<layer number="121" name="_tsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="122" name="_bsilk" color="7" fill="1" visible="yes" active="yes"/>
<layer number="123" name="tTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="124" name="bTestmark" color="7" fill="1" visible="yes" active="yes"/>
<layer number="125" name="_tNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="126" name="_bNames" color="7" fill="1" visible="yes" active="yes"/>
<layer number="127" name="_tValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="128" name="_bValues" color="7" fill="1" visible="yes" active="yes"/>
<layer number="129" name="Mask" color="7" fill="1" visible="yes" active="yes"/>
<layer number="131" name="tAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="132" name="bAdjust" color="7" fill="1" visible="yes" active="yes"/>
<layer number="144" name="Drill_legend" color="7" fill="1" visible="yes" active="yes"/>
<layer number="150" name="Notes" color="7" fill="1" visible="yes" active="yes"/>
<layer number="151" name="HeatSink" color="7" fill="1" visible="yes" active="yes"/>
<layer number="152" name="_bDocu" color="7" fill="1" visible="yes" active="yes"/>
<layer number="153" name="FabDoc1" color="7" fill="1" visible="yes" active="yes"/>
<layer number="154" name="FabDoc2" color="7" fill="1" visible="yes" active="yes"/>
<layer number="155" name="FabDoc3" color="7" fill="1" visible="yes" active="yes"/>
<layer number="199" name="Contour" color="7" fill="1" visible="yes" active="yes"/>
<layer number="200" name="200bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="201" name="201bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="202" name="202bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="203" name="203bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="204" name="204bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="205" name="205bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="206" name="206bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="207" name="207bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="208" name="208bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="209" name="209bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="210" name="210bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="211" name="211bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="212" name="212bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="213" name="213bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="214" name="214bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="215" name="215bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="216" name="216bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="217" name="217bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="218" name="218bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="219" name="219bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="220" name="220bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="221" name="221bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="222" name="222bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="223" name="223bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="224" name="224bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="225" name="225bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="226" name="226bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="227" name="227bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="228" name="228bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="229" name="229bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="230" name="230bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="231" name="231bmp" color="7" fill="1" visible="yes" active="yes"/>
<layer number="248" name="Housing" color="7" fill="1" visible="yes" active="yes"/>
<layer number="249" name="Edge" color="7" fill="1" visible="yes" active="yes"/>
<layer number="250" name="Descript" color="7" fill="1" visible="yes" active="yes"/>
<layer number="251" name="SMDround" color="7" fill="1" visible="yes" active="yes"/>
<layer number="254" name="cooling" color="7" fill="1" visible="yes" active="yes"/>
<layer number="255" name="routoute" color="7" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="TT7">
<packages>
<package name="I547-2P3_TCXO">
<description>I547-2P3-32.0000M TCXO</description>
<smd name="1" x="-1.2" y="-1" dx="1.3" dy="1.2" layer="1" rot="R90"/>
<smd name="4" x="-1.2" y="1" dx="1.3" dy="1.2" layer="1" rot="R90"/>
<smd name="3" x="1.2" y="1" dx="1.3" dy="1.2" layer="1" rot="R90"/>
<smd name="2" x="1.2" y="-1" dx="1.3" dy="1.2" layer="1" rot="R90"/>
<wire x1="-0.3" y1="1.3" x2="0.3" y2="1.3" width="0.2" layer="21"/>
<wire x1="-1.6" y1="0.1" x2="-1.6" y2="-0.1" width="0.2" layer="21"/>
<wire x1="-0.3" y1="-1.3" x2="0.3" y2="-1.3" width="0.2" layer="21"/>
<wire x1="1.6" y1="-0.1" x2="1.6" y2="0.1" width="0.2" layer="21"/>
<text x="-1" y="2" size="1" layer="27">&gt;Value</text>
<text x="-1" y="-3" size="1" layer="25">&gt;Name</text>
<wire x1="-0.35" y1="-0.1" x2="-0.8" y2="-0.1" width="0.15" layer="21"/>
<wire x1="-0.35" y1="-0.1" x2="-0.35" y2="-0.55" width="0.15" layer="21"/>
</package>
<package name="IND0402">
<description>INDUCTOR 0402 - 1 x 0.5 x 0.35mm</description>
<smd name="P$1" x="-0.5" y="0" dx="0.6" dy="0.5" layer="1" rot="R90"/>
<smd name="P$2" x="0.5" y="0" dx="0.6" dy="0.5" layer="1" rot="R90"/>
<text x="-1.010734375" y="0.581378125" size="0.5" layer="27">&gt;Value</text>
<text x="-1" y="-1" size="0.5" layer="25">&gt;Name</text>
<wire x1="-0.025" y1="0" x2="0.025" y2="0" width="0.2" layer="21"/>
</package>
<package name="CAP0402">
<description>CAPACITOR 0402 - 1 x 0.5 x 0.35mm</description>
<smd name="P$1" x="-0.5" y="0" dx="0.6" dy="0.5" layer="1" rot="R90"/>
<smd name="P$2" x="0.5" y="0" dx="0.6" dy="0.5" layer="1" rot="R90"/>
<text x="-1.010734375" y="0.581378125" size="0.5" layer="27">&gt;Value</text>
<text x="-1" y="-1" size="0.5" layer="25">&gt;Name</text>
<wire x1="-0.05" y1="0.25" x2="0.05" y2="0.25" width="0.2" layer="21"/>
<wire x1="-0.05" y1="-0.25" x2="0.05" y2="-0.25" width="0.2" layer="21"/>
</package>
<package name="RES0402">
<description>RESISTOR 0402 - 1 x 0.5 x 0.35mm</description>
<smd name="P$1" x="-0.5" y="0" dx="0.6" dy="0.5" layer="1" rot="R90"/>
<smd name="P$2" x="0.5" y="0" dx="0.6" dy="0.5" layer="1" rot="R90"/>
<text x="-1.010734375" y="0.581378125" size="0.5" layer="27">&gt;Value</text>
<text x="-1" y="-1" size="0.5" layer="25">&gt;Name</text>
<wire x1="0" y1="-0.25" x2="0" y2="0.25" width="0.2" layer="21"/>
</package>
<package name="PAD-2.5X1.5">
<description>Pad - 2.5 x 1.5 mm</description>
<smd name="P$1" x="0" y="0" dx="2.5" dy="1.5" layer="1"/>
<text x="-1" y="1" size="0.75" layer="27">&gt;Value</text>
<text x="-1" y="-2" size="0.75" layer="25">&gt;Name</text>
</package>
<package name="HOLE-1.87">
<description>Hole - 1.016/1.87 mm</description>
<pad name="P$1" x="0" y="0" drill="1.016" diameter="1.87" shape="octagon"/>
<text x="-1" y="1.22464375" size="0.75" layer="27">&gt;Value</text>
<text x="-1" y="-2" size="0.75" layer="25">&gt;Name</text>
</package>
<package name="LTC3105">
<description>LTC3105 MSOP-12</description>
<circle x="-1.305003125" y="-0.6514375" radius="0.221040625" width="0.127" layer="21"/>
<wire x1="2" y1="1.5" x2="-2" y2="1.5" width="0.127" layer="51"/>
<wire x1="-2" y1="1.5" x2="-2" y2="-1.5" width="0.127" layer="51"/>
<wire x1="-2" y1="-1.5" x2="2" y2="-1.5" width="0.127" layer="51"/>
<wire x1="2" y1="-1.5" x2="2" y2="1.5" width="0.127" layer="51"/>
<wire x1="-2" y1="1.4" x2="2" y2="1.4" width="0.2" layer="21"/>
<wire x1="2" y1="1.4" x2="2" y2="-1.4" width="0.2" layer="21"/>
<wire x1="2" y1="-1.4" x2="-2" y2="-1.4" width="0.2" layer="21"/>
<wire x1="-2" y1="-1.4" x2="-2" y2="1.4" width="0.2" layer="21"/>
<smd name="1" x="-1.625" y="-2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="2" x="-0.975" y="-2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="3" x="-0.325" y="-2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="4" x="0.325" y="-2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="5" x="0.975" y="-2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="6" x="1.625" y="-2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="7" x="1.625" y="2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="8" x="0.975" y="2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="9" x="0.325" y="2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="10" x="-0.325" y="2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="11" x="-0.975" y="2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<smd name="12" x="-1.625" y="2.165" dx="0.9" dy="0.42" layer="1" rot="R90"/>
<text x="-0.849978125" y="0.349990625" size="0.6" layer="27">&gt;Value</text>
<text x="-0.8833125" y="-0.91664375" size="0.6" layer="25">&gt;Name</text>
</package>
<package name="DLJ4018">
<description>FERROCORE DLJ4018-10uH</description>
<smd name="P$1" x="-1.6" y="0" dx="1.2" dy="2" layer="1"/>
<smd name="P$2" x="1.6" y="0" dx="1.2" dy="2" layer="1"/>
<wire x1="-1.95" y1="1.95" x2="1.95" y2="1.95" width="0.2" layer="21"/>
<wire x1="-1.95" y1="-1.95" x2="1.95" y2="-1.95" width="0.2" layer="21"/>
<wire x1="1.95" y1="1.95" x2="1.95" y2="1.5" width="0.2" layer="21"/>
<wire x1="1.95" y1="-1.95" x2="1.95" y2="-1.5" width="0.2" layer="21"/>
<wire x1="-1.95" y1="-1.95" x2="-1.95" y2="-1.5" width="0.2" layer="21"/>
<wire x1="-1.95" y1="1.95" x2="-1.95" y2="1.5" width="0.2" layer="21"/>
<text x="-2" y="3" size="1" layer="27">&gt;Value</text>
<text x="-2" y="-4" size="1" layer="25">&gt;Name</text>
</package>
<package name="CAP0805">
<description>CAPACITOR 0805 - 2.0 x 1.2 x 0.45mm</description>
<smd name="P$1" x="-0.95" y="0" dx="1.3" dy="0.7" layer="1" rot="R90"/>
<smd name="P$2" x="0.95" y="0" dx="1.3" dy="0.7" layer="1" rot="R90"/>
<text x="-1.002078125" y="0.9977375" size="0.5" layer="27">&gt;Value</text>
<text x="-1" y="-1.477078125" size="0.5" layer="25">&gt;Name</text>
<wire x1="-0.15" y1="0.5" x2="0.15" y2="0.5" width="0.2" layer="21"/>
<wire x1="-0.15" y1="-0.5" x2="0.15" y2="-0.5" width="0.2" layer="21"/>
</package>
<package name="CAP0603">
<description>CAPACITOR 0603 - 1.55 x 0.85 x 0.45mm</description>
<smd name="P$1" x="-0.75" y="0" dx="0.9" dy="0.6" layer="1" rot="R90"/>
<smd name="P$2" x="0.75" y="0" dx="0.9" dy="0.6" layer="1" rot="R90"/>
<text x="-1.002078125" y="0.9977375" size="0.5" layer="27">&gt;Value</text>
<text x="-1" y="-1.477078125" size="0.5" layer="25">&gt;Name</text>
<wire x1="-0.05" y1="0.25" x2="0.05" y2="0.25" width="0.2" layer="21"/>
<wire x1="-0.05" y1="-0.25" x2="0.05" y2="-0.25" width="0.2" layer="21"/>
</package>
<package name="DLJ3015">
<description>FERROCORE DLJ3015-2.2uH</description>
<smd name="P$1" x="-1.2" y="0" dx="1" dy="1.6" layer="1"/>
<smd name="P$2" x="1.2" y="0" dx="1" dy="1.6" layer="1"/>
<wire x1="-1.45" y1="1.45" x2="1.45" y2="1.45" width="0.2" layer="21"/>
<wire x1="-1.45" y1="-1.45" x2="1.45" y2="-1.45" width="0.2" layer="21"/>
<wire x1="1.45" y1="1.45" x2="1.45" y2="1.1" width="0.2" layer="21"/>
<wire x1="1.45" y1="-1.45" x2="1.45" y2="-1.1" width="0.2" layer="21"/>
<wire x1="-1.45" y1="-1.45" x2="-1.45" y2="-1.1" width="0.2" layer="21"/>
<wire x1="-1.45" y1="1.45" x2="-1.45" y2="1.1" width="0.2" layer="21"/>
<text x="-2" y="3" size="1" layer="27">&gt;Value</text>
<text x="-2" y="-4" size="1" layer="25">&gt;Name</text>
</package>
<package name="UBLOX_MAX-7C">
<description>uBlox MAX</description>
<circle x="2.85" y="-3.95" radius="0.6" width="0" layer="21"/>
<wire x1="-4.65" y1="-4.9" x2="-4.65" y2="-5.15" width="0.1" layer="21"/>
<wire x1="-4.65" y1="-5.15" x2="5.05" y2="-5.15" width="0.1" layer="21"/>
<wire x1="5.05" y1="-4.9" x2="5.05" y2="-5.15" width="0.1" layer="21"/>
<wire x1="-4.65" y1="4.95" x2="5.05" y2="4.95" width="0.1" layer="21"/>
<wire x1="5.05" y1="4.95" x2="5.05" y2="4.8" width="0.1" layer="21"/>
<wire x1="-4.65" y1="4.95" x2="-4.65" y2="4.8" width="0.1" layer="21"/>
<smd name="1_GND" x="4.95" y="-4.4" dx="1.8" dy="0.7" layer="1"/>
<smd name="2_TXD1" x="4.95" y="-3.35" dx="1.8" dy="0.8" layer="1"/>
<smd name="3_RXD1" x="4.95" y="-2.25" dx="1.8" dy="0.8" layer="1"/>
<smd name="4_TIMEPULSE" x="4.95" y="-1.15" dx="1.8" dy="0.8" layer="1"/>
<smd name="5_EXTINT0" x="4.95" y="-0.05" dx="1.8" dy="0.8" layer="1"/>
<smd name="6_V_BCKP" x="4.95" y="1.05" dx="1.8" dy="0.8" layer="1"/>
<smd name="7_VCC_IO" x="4.95" y="2.15" dx="1.8" dy="0.8" layer="1"/>
<smd name="8_VCC" x="4.95" y="3.25" dx="1.8" dy="0.8" layer="1"/>
<smd name="9_V_RESET" x="4.95" y="4.3" dx="1.8" dy="0.7" layer="1"/>
<smd name="10_GND" x="-4.55" y="4.3" dx="1.8" dy="0.7" layer="1"/>
<smd name="11_RF_IN" x="-4.55" y="3.25" dx="1.8" dy="0.8" layer="1"/>
<smd name="12_GND" x="-4.55" y="2.15" dx="1.8" dy="0.8" layer="1"/>
<smd name="13_ANTON" x="-4.55" y="1.05" dx="1.8" dy="0.8" layer="1"/>
<smd name="14_VCC_RF" x="-4.55" y="-0.05" dx="1.8" dy="0.8" layer="1"/>
<smd name="15_RESERVED" x="-4.55" y="-1.15" dx="1.8" dy="0.8" layer="1"/>
<smd name="16_SDA2" x="-4.55" y="-2.25" dx="1.8" dy="0.8" layer="1"/>
<smd name="17_SCL2" x="-4.55" y="-3.35" dx="1.8" dy="0.8" layer="1"/>
<smd name="18_RESERVED" x="-4.55" y="-4.4" dx="1.8" dy="0.7" layer="1"/>
<text x="3.35875" y="-3.10625" size="0.8128" layer="21" font="vector" ratio="15" rot="R90">ublox</text>
</package>
<package name="RES0603">
<description>RESISTOR 0603 - 1.55 x 0.85 x 0.45mm</description>
<smd name="P$1" x="-0.75" y="0" dx="0.9" dy="0.6" layer="1" rot="R90"/>
<smd name="P$2" x="0.75" y="0" dx="0.9" dy="0.6" layer="1" rot="R90"/>
<text x="-1.002078125" y="1.006409375" size="0.5" layer="27">&gt;Value</text>
<text x="-1" y="-1.390334375" size="0.5" layer="25">&gt;Name</text>
<wire x1="0" y1="-0.25" x2="0" y2="0.25" width="0.2" layer="21"/>
</package>
<package name="LED0603">
<description>LED 0603</description>
<smd name="ANODE" x="-0.75" y="0" dx="0.8" dy="0.8" layer="1" rot="R90"/>
<smd name="CATHODE" x="0.75" y="0" dx="0.8" dy="0.8" layer="1" rot="R90"/>
<text x="-1" y="1" size="0.5" layer="27">&gt;Value</text>
<text x="-0.998246875" y="-1.330996875" size="0.5" layer="25">&gt;Name</text>
<wire x1="-0.14" y1="-0.33" x2="-0.14" y2="0.33" width="0.15" layer="21"/>
<wire x1="0.18" y1="0" x2="-0.14" y2="0.33" width="0.15" layer="21"/>
<wire x1="0.18" y1="0" x2="-0.14" y2="-0.33" width="0.15" layer="21"/>
</package>
<package name="SAM3S8B-AU">
<description>SAM3S8B-AU</description>
<smd name="63" x="-3.25" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="64" x="-3.75" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="62" x="-2.75" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="60" x="-1.75" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="58" x="-0.75" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="56" x="0.25" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="54" x="1.25" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="52" x="2.25" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="50" x="3.25" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="61" x="-2.25" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="59" x="-1.25" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="57" x="-0.25" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="55" x="0.75" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="53" x="1.75" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="51" x="2.75" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="49" x="3.75" y="5.6" dx="1.2" dy="0.3" layer="1" rot="R90"/>
<smd name="31" x="3.25" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="32" x="3.75" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="30" x="2.75" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="28" x="1.75" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="26" x="0.75" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="24" x="-0.25" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="22" x="-1.25" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="20" x="-2.25" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="18" x="-3.25" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="29" x="2.25" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="27" x="1.25" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="25" x="0.25" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="23" x="-0.75" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="21" x="-1.75" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="19" x="-2.75" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="17" x="-3.75" y="-5.6" dx="1.2" dy="0.3" layer="1" rot="R270"/>
<smd name="47" x="5.6" y="3.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="48" x="5.6" y="3.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="46" x="5.6" y="2.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="44" x="5.6" y="1.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="42" x="5.6" y="0.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="40" x="5.6" y="-0.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="38" x="5.6" y="-1.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="36" x="5.6" y="-2.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="34" x="5.6" y="-3.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="45" x="5.6" y="2.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="43" x="5.6" y="1.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="41" x="5.6" y="0.25" dx="1.2" dy="0.3" layer="1"/>
<smd name="39" x="5.6" y="-0.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="37" x="5.6" y="-1.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="35" x="5.6" y="-2.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="33" x="5.6" y="-3.75" dx="1.2" dy="0.3" layer="1"/>
<smd name="15" x="-5.6" y="-3.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="16" x="-5.6" y="-3.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="14" x="-5.6" y="-2.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="12" x="-5.6" y="-1.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="10" x="-5.6" y="-0.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="8" x="-5.6" y="0.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="6" x="-5.6" y="1.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="4" x="-5.6" y="2.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="2" x="-5.6" y="3.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="13" x="-5.6" y="-2.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="11" x="-5.6" y="-1.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="9" x="-5.6" y="-0.25" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="7" x="-5.6" y="0.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="5" x="-5.6" y="1.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="3" x="-5.6" y="2.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<smd name="1" x="-5.6" y="3.75" dx="1.2" dy="0.3" layer="1" rot="R180"/>
<wire x1="-5" y1="4.2" x2="-5" y2="5" width="0.2" layer="21"/>
<wire x1="-5" y1="5" x2="-4.2" y2="5" width="0.2" layer="21"/>
<wire x1="-5" y1="-4.2" x2="-5" y2="-5" width="0.2" layer="21"/>
<wire x1="-5" y1="-5" x2="-4.2" y2="-5" width="0.2" layer="21"/>
<wire x1="4.2" y1="-5" x2="5" y2="-5" width="0.2" layer="21"/>
<wire x1="5" y1="-5" x2="5" y2="-4.2" width="0.2" layer="21"/>
<wire x1="5" y1="4.2" x2="5" y2="5" width="0.2" layer="21"/>
<wire x1="5" y1="5" x2="4.2" y2="5" width="0.2" layer="21"/>
<circle x="-4" y="4" radius="0.2" width="0.2" layer="21"/>
<text x="-2" y="2" size="1" layer="27">&gt;Value</text>
<text x="-2" y="-3" size="1" layer="25">&gt;Name</text>
</package>
<package name="CFPX-104">
<description>CFPX-104 Crystal Oscillator</description>
<smd name="4" x="-1.9" y="1.15" dx="1.6" dy="1.4" layer="1"/>
<smd name="3" x="1.9" y="1.15" dx="1.6" dy="1.4" layer="1"/>
<smd name="2" x="1.9" y="-1.15" dx="1.6" dy="1.4" layer="1"/>
<smd name="1" x="-1.9" y="-1.15" dx="1.6" dy="1.4" layer="1"/>
<wire x1="-0.8" y1="1.6" x2="0.8" y2="1.6" width="0.15" layer="21"/>
<wire x1="-0.8" y1="-1.6" x2="0.8" y2="-1.6" width="0.15" layer="21"/>
<wire x1="2.4" y1="0.2" x2="2.4" y2="-0.2" width="0.15" layer="21"/>
<wire x1="-2.4" y1="0.2" x2="-2.4" y2="-0.2" width="0.15" layer="21"/>
<wire x1="-1.2" y1="-0.2" x2="-0.8" y2="-0.2" width="0.15" layer="21"/>
<wire x1="-0.8" y1="-0.2" x2="-0.8" y2="-0.6" width="0.15" layer="21"/>
<text x="-2" y="3" size="0.7" layer="25">&gt;Name</text>
<text x="-2" y="-4" size="0.7" layer="27">&gt;Value</text>
</package>
<package name="USB_MICRO_B">
<description>USB Micro-B connector</description>
<smd name="D-" x="-0.65" y="2.73" dx="1.55" dy="0.4" layer="1" rot="R90"/>
<smd name="D+" x="0" y="2.73" dx="1.55" dy="0.4" layer="1" rot="R90"/>
<smd name="ID" x="0.65" y="2.73" dx="1.55" dy="0.4" layer="1" rot="R90"/>
<smd name="GND" x="1.3" y="2.73" dx="1.55" dy="0.4" layer="1" rot="R90"/>
<smd name="VBUS" x="-1.3" y="2.73" dx="1.55" dy="0.4" layer="1" rot="R90"/>
<pad name="P$6" x="-3.575" y="0" drill="1.2" diameter="1.8" shape="square" rot="R90"/>
<pad name="P$7" x="3.575" y="0" drill="1.2" diameter="1.8" shape="square" rot="R90"/>
<wire x1="-3.7" y1="-2.73" x2="3.7" y2="-2.73" width="0.1" layer="51"/>
<wire x1="-3.7" y1="2.73" x2="-3.7" y2="-2.73" width="0.1" layer="51"/>
<wire x1="3.7" y1="2.73" x2="3.7" y2="-2.73" width="0.1" layer="51"/>
<wire x1="-3.7" y1="2.73" x2="3.7" y2="2.73" width="0.1" layer="51"/>
<pad name="P$8" x="-2.425" y="2.73" drill="0.9"/>
<pad name="P$9" x="2.425" y="2.73" drill="0.9"/>
<wire x1="-3.8" y1="1.1" x2="-3.8" y2="2.8" width="0.15" layer="21"/>
<wire x1="-3.8" y1="2.8" x2="-3.3" y2="2.8" width="0.15" layer="21"/>
<wire x1="3.3" y1="2.8" x2="3.8" y2="2.8" width="0.15" layer="21"/>
<wire x1="3.8" y1="2.8" x2="3.8" y2="1.1" width="0.15" layer="21"/>
<text x="-5" y="-3" size="1" layer="25" rot="R90">&gt;Name</text>
<text x="6" y="-3" size="1" layer="27" rot="R90">&gt;Value</text>
</package>
<package name="MCP1700">
<description>MCP1700 - SOT-23 package</description>
<smd name="3" x="0" y="1.15" dx="0.65" dy="1.05" layer="1"/>
<smd name="1" x="-0.95" y="-1.15" dx="0.65" dy="1.05" layer="1"/>
<smd name="2" x="0.95" y="-1.15" dx="0.65" dy="1.05" layer="1"/>
<wire x1="0.55" y1="0.65" x2="1.49" y2="0.65" width="0.15" layer="21"/>
<wire x1="0.4" y1="-0.65" x2="-0.4" y2="-0.65" width="0.15" layer="21"/>
<wire x1="1.49" y1="0.65" x2="1.49" y2="-0.65" width="0.15" layer="21"/>
<wire x1="-1.49" y1="-0.65" x2="-1.49" y2="0.65" width="0.15" layer="21"/>
<wire x1="-1.49" y1="0.65" x2="-0.55" y2="0.65" width="0.15" layer="21"/>
<circle x="-1" y="-0.2" radius="0.1" width="0.15" layer="21"/>
<text x="-2" y="2" size="1" layer="25">&gt;Name</text>
<text x="-2" y="-3" size="1" layer="27">&gt;Value</text>
</package>
<package name="PAD-3X1.5">
<description>Pad - 3 x 1.5 mm</description>
<smd name="P$1" x="0" y="0" dx="3" dy="1.5" layer="1"/>
<text x="-2" y="1" size="0.75" layer="27">&gt;Value</text>
<text x="-2" y="-2" size="0.75" layer="25">&gt;Name</text>
</package>
<package name="MT9D111-AVX145602-NEW">
<description>MT9D111 - AVX145602‐030000‐829 connector</description>
<smd name="9" x="-0.4" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="8" x="0" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="7" x="0.4" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="6" x="0.8" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="5" x="1.2" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="10" x="-0.8" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="11" x="-1.2" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="12" x="-1.6" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="4" x="1.6" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="3" x="2" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="2" x="2.4" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="29" x="2.4" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="13" x="-2" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="18" x="-2" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="28" x="2" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="27" x="1.6" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="26" x="1.2" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="25" x="0.8" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="24" x="0.4" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="19" x="-1.6" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="20" x="-1.2" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="21" x="-0.8" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="22" x="-0.4" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="23" x="0" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="17" x="-2.4" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="14" x="-2.4" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="15" x="-2.8" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="16" x="-2.8" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="30" x="2.8" y="1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<smd name="1" x="2.8" y="-1.75" dx="1" dy="0.23" layer="1" rot="R90"/>
<wire x1="-5" y1="6.55" x2="-4" y2="6.55" width="0.03" layer="51" style="shortdash"/>
<wire x1="-4" y1="6.55" x2="4" y2="6.55" width="0.03" layer="51" style="shortdash"/>
<wire x1="4" y1="6.55" x2="5" y2="6.55" width="0.03" layer="51" style="shortdash"/>
<wire x1="5" y1="6.55" x2="5" y2="16.55" width="0.03" layer="51" style="shortdash"/>
<wire x1="5" y1="16.55" x2="-5" y2="16.55" width="0.03" layer="51" style="shortdash"/>
<wire x1="-5" y1="16.55" x2="-5" y2="6.55" width="0.03" layer="51" style="shortdash"/>
<wire x1="-4" y1="6.55" x2="-4" y2="3.05" width="0.03" layer="51" style="shortdash"/>
<wire x1="4" y1="6.55" x2="4" y2="3.05" width="0.03" layer="51" style="shortdash"/>
<wire x1="5" y1="3.05" x2="5" y2="-3.05" width="0.03" layer="51" style="shortdash"/>
<wire x1="-5" y1="3.05" x2="-5" y2="-3.05" width="0.03" layer="51" style="shortdash"/>
<wire x1="-5" y1="3.05" x2="5" y2="3.05" width="0.03" layer="51" style="shortdash"/>
<wire x1="5" y1="-3.05" x2="-5" y2="-3.05" width="0.03" layer="51" style="shortdash"/>
<text x="6" y="2" size="1.016" layer="27">&gt;Value</text>
<text x="6" y="-2" size="1.016" layer="25">&gt;Name</text>
<wire x1="-3.5" y1="-1.25" x2="-3.5" y2="1.25" width="0.03" layer="51"/>
<wire x1="-3.5" y1="1.25" x2="3.5" y2="1.25" width="0.03" layer="51"/>
<wire x1="3.5" y1="1.25" x2="3.5" y2="-1.25" width="0.03" layer="51"/>
<wire x1="3.5" y1="-1.25" x2="-3.5" y2="-1.25" width="0.03" layer="51"/>
<wire x1="-3" y1="1" x2="-3" y2="2" width="0.03" layer="51" style="shortdash"/>
<wire x1="-3" y1="2" x2="3" y2="2" width="0.03" layer="51" style="shortdash"/>
<wire x1="3" y1="2" x2="3" y2="1" width="0.03" layer="51" style="shortdash"/>
<wire x1="3" y1="1" x2="-3" y2="1" width="0.03" layer="51" style="shortdash"/>
<wire x1="-3" y1="-1" x2="3" y2="-1" width="0.03" layer="51" style="shortdash"/>
<wire x1="3" y1="-1" x2="3" y2="-2" width="0.03" layer="51" style="shortdash"/>
<wire x1="3" y1="-2" x2="-3" y2="-2" width="0.03" layer="51" style="shortdash"/>
<wire x1="-3" y1="-2" x2="-3" y2="-1" width="0.03" layer="51" style="shortdash"/>
</package>
<package name="SI4060_VIAS">
<description>SI4060 with GND vias.</description>
<smd name="GNDP" x="0" y="0" dx="2.6" dy="2.6" layer="1"/>
<smd name="P15" x="1.975" y="1" dx="0.7" dy="0.25" layer="1"/>
<smd name="P13" x="1.975" y="0" dx="0.7" dy="0.25" layer="1"/>
<smd name="P11" x="1.975" y="-1" dx="0.7" dy="0.25" layer="1"/>
<smd name="P12" x="1.975" y="-0.5" dx="0.7" dy="0.25" layer="1"/>
<smd name="P14" x="1.975" y="0.5" dx="0.7" dy="0.25" layer="1"/>
<smd name="P1" x="-1.975" y="1" dx="0.7" dy="0.25" layer="1"/>
<smd name="P3" x="-1.975" y="0" dx="0.7" dy="0.25" layer="1"/>
<smd name="P5" x="-1.975" y="-1" dx="0.7" dy="0.25" layer="1"/>
<smd name="P4" x="-1.975" y="-0.5" dx="0.7" dy="0.25" layer="1"/>
<smd name="P2" x="-1.975" y="0.5" dx="0.7" dy="0.25" layer="1"/>
<smd name="P20" x="-1" y="1.975" dx="0.25" dy="0.7" layer="1"/>
<smd name="P19" x="-0.5" y="1.975" dx="0.25" dy="0.7" layer="1"/>
<smd name="P18" x="0" y="1.975" dx="0.25" dy="0.7" layer="1"/>
<smd name="P17" x="0.5" y="1.975" dx="0.25" dy="0.7" layer="1"/>
<smd name="P16" x="1" y="1.975" dx="0.25" dy="0.7" layer="1"/>
<smd name="P6" x="-1" y="-1.975" dx="0.25" dy="0.7" layer="1"/>
<smd name="P7" x="-0.5" y="-1.975" dx="0.25" dy="0.7" layer="1"/>
<smd name="P8" x="0" y="-1.975" dx="0.25" dy="0.7" layer="1"/>
<smd name="P9" x="0.5" y="-1.975" dx="0.25" dy="0.7" layer="1"/>
<smd name="P10" x="1" y="-1.975" dx="0.25" dy="0.7" layer="1"/>
<circle x="-1.7" y="1.7" radius="0.16" width="0.16" layer="21"/>
<wire x1="-2" y1="-1.5" x2="-2" y2="-2" width="0.2" layer="21"/>
<wire x1="-2" y1="-2" x2="-1.5" y2="-2" width="0.2" layer="21"/>
<wire x1="2" y1="-2" x2="2" y2="-1.5" width="0.2" layer="21"/>
<wire x1="2" y1="-2" x2="1.5" y2="-2" width="0.2" layer="21"/>
<wire x1="1.5" y1="2" x2="2" y2="2" width="0.2" layer="21"/>
<wire x1="2" y1="2" x2="2" y2="1.5" width="0.2" layer="21"/>
<text x="-2" y="3" size="1.016" layer="27">&gt;Value</text>
<text x="-2" y="-4" size="1.016" layer="25">&gt;Name</text>
<pad name="GNDV1" x="-0.65" y="-0.65" drill="0.34"/>
<pad name="GNDV2" x="0.65" y="0.65" drill="0.34"/>
</package>
<package name="TPS63031_VIAS">
<description>TPS63031 with GND vias.</description>
<wire x1="-1.4" y1="1.31" x2="1.4" y2="1.31" width="0.16" layer="21"/>
<wire x1="-1.4" y1="-1.33" x2="1.4" y2="-1.33" width="0.16" layer="21"/>
<smd name="1" x="-1.25" y="1" dx="0.8" dy="0.28" layer="1" roundness="75"/>
<smd name="2" x="-1.25" y="0.5" dx="0.8" dy="0.28" layer="1" roundness="75"/>
<smd name="3" x="-1.25" y="0" dx="0.8" dy="0.28" layer="1" roundness="75"/>
<smd name="4" x="-1.25" y="-0.5" dx="0.8" dy="0.28" layer="1" roundness="75"/>
<smd name="5" x="-1.25" y="-1" dx="0.8" dy="0.28" layer="1" roundness="75"/>
<smd name="6" x="1.25" y="-1" dx="0.8" dy="0.28" layer="1" roundness="75"/>
<smd name="7" x="1.25" y="-0.5" dx="0.8" dy="0.28" layer="1" roundness="75"/>
<smd name="8" x="1.25" y="0" dx="0.8" dy="0.28" layer="1" roundness="75"/>
<smd name="9" x="1.25" y="0.5" dx="0.8" dy="0.28" layer="1" roundness="75"/>
<smd name="10" x="1.25" y="1" dx="0.8" dy="0.28" layer="1" roundness="75"/>
<smd name="11" x="0" y="0" dx="1.2" dy="2" layer="1"/>
<text x="-1" y="2" size="0.6096" layer="25">&gt;Name</text>
<text x="-0.999975" y="-2.527715625" size="0.6096" layer="27">&gt;Value</text>
<wire x1="-0.3" y1="1.17" x2="-0.65" y2="1.17" width="0.16" layer="21"/>
<pad name="VIA1" x="0" y="0.5" drill="0.34"/>
<pad name="VIA2" x="0" y="-0.5" drill="0.34"/>
</package>
<package name="ME6211_NEW">
<description>ME6211-1.8 and ME6211-2.8 in SOT23-5 package without silkscreen.</description>
<smd name="1" x="-0.95" y="-1.1" dx="1.06" dy="0.65" layer="1" rot="R90"/>
<smd name="2" x="0" y="-1.1" dx="1.06" dy="0.65" layer="1" rot="R90"/>
<smd name="3" x="0.95" y="-1.1" dx="1.06" dy="0.65" layer="1" rot="R90"/>
<smd name="4" x="0.95" y="1.1" dx="1.06" dy="0.65" layer="1" rot="R90"/>
<smd name="5" x="-0.95" y="1.1" dx="1.06" dy="0.65" layer="1" rot="R90"/>
<text x="-2" y="2" size="1" layer="27">&gt;Value</text>
<text x="-2" y="-3" size="1" layer="25">&gt;Name</text>
</package>
</packages>
<symbols>
<symbol name="I547-2P3_TCXO">
<description>I547-2P3-32.0000M TCXO</description>
<pin name="VDD" x="-15.24" y="2.54" length="short"/>
<pin name="NC" x="-15.24" y="-2.54" length="short"/>
<pin name="OUT" x="15.24" y="2.54" length="short" rot="R180"/>
<pin name="GND" x="15.24" y="-2.54" length="short" rot="R180"/>
<wire x1="-2.54" y1="5.08" x2="2.54" y2="5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="5.08" x2="2.54" y2="-5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="-5.08" x2="-2.54" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-2.54" y1="-5.08" x2="-2.54" y2="5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-5.08" x2="-5.08" y2="0" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="12.7" y2="0" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-12.7" y2="0" width="0.254" layer="94"/>
<wire x1="12.7" y1="0" x2="12.7" y2="2.54" width="0.254" layer="94"/>
<wire x1="12.7" y1="0" x2="12.7" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-12.7" y1="0" x2="-12.7" y2="2.54" width="0.254" layer="94"/>
<wire x1="-12.7" y1="0" x2="-12.7" y2="-2.54" width="0.254" layer="94"/>
<text x="-7.62" y="7.62" size="2.54" layer="96">&gt;Value</text>
<text x="-7.62" y="-10.16" size="2.54" layer="95">&gt;Name</text>
</symbol>
<symbol name="INDUCTOR">
<description>INDUCTOR</description>
<pin name="P$1" x="-7.62" y="0" visible="off" length="short"/>
<pin name="P$2" x="7.62" y="0" visible="off" length="short" rot="R180"/>
<text x="-5.08" y="3.302" size="1.905" layer="96">&gt;Value</text>
<text x="-5.08" y="-3.556" size="1.905" layer="95">&gt;Name</text>
<wire x1="-5.08" y1="0" x2="-2.54" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="-2.54" y1="0" x2="0" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.254" layer="94" curve="-180"/>
<wire x1="2.54" y1="0" x2="5.08" y2="0" width="0.254" layer="94" curve="-180"/>
</symbol>
<symbol name="CAPACITOR">
<description>CAPACITOR</description>
<pin name="P$1" x="-5.08" y="0" visible="off" length="short"/>
<pin name="P$2" x="5.08" y="0" visible="off" length="short" rot="R180"/>
<text x="-5.08" y="3.302" size="1.905" layer="96">&gt;Value</text>
<text x="-5.08" y="-5.08" size="1.905" layer="95">&gt;Name</text>
<wire x1="-0.635" y1="-2.54" x2="-0.635" y2="0" width="0.254" layer="94"/>
<wire x1="-0.635" y1="0" x2="-0.635" y2="2.54" width="0.254" layer="94"/>
<wire x1="0.635" y1="2.54" x2="0.635" y2="0" width="0.254" layer="94"/>
<wire x1="0.635" y1="0" x2="0.635" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="-0.635" y2="0" width="0.254" layer="94"/>
<wire x1="2.54" y1="0" x2="0.635" y2="0" width="0.254" layer="94"/>
</symbol>
<symbol name="RESISTOR">
<description>RESISTOR</description>
<pin name="P$1" x="-7.62" y="0" visible="off" length="short"/>
<pin name="P$2" x="7.62" y="0" visible="off" length="short" rot="R180"/>
<wire x1="-2.286" y1="-1.524" x2="-1.524" y2="1.524" width="0.254" layer="94"/>
<wire x1="-1.524" y1="1.524" x2="-0.762" y2="-1.524" width="0.254" layer="94"/>
<wire x1="-0.762" y1="-1.524" x2="0" y2="1.524" width="0.254" layer="94"/>
<wire x1="0" y1="1.524" x2="0.762" y2="-1.524" width="0.254" layer="94"/>
<wire x1="0.762" y1="-1.524" x2="1.524" y2="1.524" width="0.254" layer="94"/>
<wire x1="1.524" y1="1.524" x2="2.286" y2="-1.524" width="0.254" layer="94"/>
<wire x1="2.286" y1="-1.524" x2="3.048" y2="1.524" width="0.254" layer="94"/>
<wire x1="3.048" y1="1.524" x2="3.556" y2="0" width="0.254" layer="94"/>
<wire x1="3.556" y1="0" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="-3.048" y1="1.524" x2="-2.286" y2="-1.524" width="0.254" layer="94"/>
<text x="-5.08" y="3.302" size="1.905" layer="96">&gt;Value</text>
<text x="-5.08" y="-5.08" size="1.905" layer="95">&gt;Name</text>
<wire x1="-3.556" y1="0" x2="-3.048" y2="1.524" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-3.556" y2="0" width="0.254" layer="94"/>
</symbol>
<symbol name="PAD">
<description>Pad</description>
<pin name="P$1" x="-5.08" y="0" visible="off" length="short"/>
<wire x1="-2.54" y1="-2.54" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-2.54" y1="0" x2="-2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="2.54" y2="2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="2.54" y2="-2.54" width="0.254" layer="94"/>
<wire x1="2.54" y1="-2.54" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<text x="-2.54" y="3.81" size="1.27" layer="96">&gt;Value</text>
<text x="-2.54" y="-5.08" size="1.27" layer="95">&gt;Name</text>
<wire x1="-2.54" y1="0" x2="-5.08" y2="0" width="0.254" layer="94"/>
</symbol>
<symbol name="HOLE">
<description>Hole</description>
<pin name="P$1" x="0" y="5.08" visible="off" length="short" rot="R270"/>
<circle x="0" y="0" radius="2.54" width="0.254" layer="94"/>
<wire x1="0" y1="2.54" x2="0" y2="5.08" width="0.254" layer="94"/>
<wire x1="2.54" y1="2.54" x2="-2.54" y2="-2.54" width="0.254" layer="94"/>
<text x="5.08" y="2.54" size="1.27" layer="96">&gt;Value</text>
<text x="5.08" y="-2.54" size="1.27" layer="95">&gt;Name</text>
</symbol>
<symbol name="LTC3105">
<description>LTC3105 MSOP-12</description>
<text x="-10" y="9.54" size="1.27" layer="95">&gt;Name</text>
<text x="-10" y="-13.08" size="1.27" layer="96">&gt;Value</text>
<pin name="FB" x="-15.24" y="5.08" visible="pin" length="short"/>
<pin name="LDO" x="-15.24" y="2.54" visible="pin" length="short"/>
<pin name="FBLDO" x="-15.24" y="0" visible="pin" length="short"/>
<pin name="!SHDN" x="-15.24" y="-2.54" visible="pin" length="short"/>
<pin name="MPPC" x="-15.24" y="-5.08" visible="pin" length="short"/>
<pin name="AUX" x="15.24" y="5.08" visible="pin" length="short" rot="R180"/>
<pin name="VOUT" x="15.24" y="2.54" visible="pin" length="short" rot="R180"/>
<pin name="PGOOD" x="15.24" y="0" visible="pin" length="short" rot="R180"/>
<pin name="SW" x="15.24" y="-2.54" visible="pin" length="short" rot="R180"/>
<pin name="VIN" x="15.24" y="-5.08" visible="pin" length="short" rot="R180"/>
<pin name="GND@6" x="-15.24" y="-7.62" visible="pin" length="short"/>
<pin name="GND@7" x="15.24" y="-7.62" visible="pin" length="short" rot="R180"/>
<wire x1="-12.7" y1="-10.16" x2="12.7" y2="-10.16" width="0.254" layer="94"/>
<wire x1="12.7" y1="-10.16" x2="12.7" y2="7.62" width="0.254" layer="94"/>
<wire x1="12.7" y1="7.62" x2="-12.7" y2="7.62" width="0.254" layer="94"/>
<wire x1="-12.7" y1="7.62" x2="-12.7" y2="-10.16" width="0.254" layer="94"/>
</symbol>
<symbol name="UBLOX_MAX-7C">
<wire x1="-17.78" y1="17.78" x2="-17.78" y2="-27.94" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-27.94" x2="17.78" y2="-27.94" width="0.254" layer="94"/>
<wire x1="17.78" y1="-27.94" x2="17.78" y2="17.78" width="0.254" layer="94"/>
<wire x1="17.78" y1="17.78" x2="-17.78" y2="17.78" width="0.254" layer="94"/>
<pin name="1_GND" x="22.86" y="-25.4" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="2_TXD1" x="22.86" y="-20.32" visible="pin" length="middle" rot="R180"/>
<pin name="3_RXD1" x="22.86" y="-15.24" visible="pin" length="middle" rot="R180"/>
<pin name="4_TIMEPULSE" x="22.86" y="-10.16" visible="pin" length="middle" rot="R180"/>
<pin name="5_EXTINT0" x="22.86" y="-5.08" visible="pin" length="middle" rot="R180"/>
<pin name="6_V_BCKP" x="22.86" y="0" visible="pin" length="middle" rot="R180"/>
<pin name="7_VCC_IO" x="22.86" y="5.08" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="8_VCC" x="22.86" y="10.16" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="9_V_RESET" x="22.86" y="15.24" visible="pin" length="middle" direction="pwr" rot="R180"/>
<pin name="10_GND" x="-22.86" y="15.24" visible="pin" length="middle" direction="pwr"/>
<pin name="11_RF_IN" x="-22.86" y="10.16" visible="pin" length="middle"/>
<pin name="12_GND" x="-22.86" y="5.08" visible="pin" length="middle" direction="pwr"/>
<pin name="13_ANTON" x="-22.86" y="0" visible="pin" length="middle"/>
<pin name="14_VCC_RF" x="-22.86" y="-5.08" visible="pin" length="middle"/>
<pin name="15_RESERVED" x="-22.86" y="-10.16" visible="pin" length="middle"/>
<pin name="16_SDA2" x="-22.86" y="-15.24" visible="pin" length="middle"/>
<pin name="17_SCL2" x="-22.86" y="-20.32" visible="pin" length="middle"/>
<pin name="18_RESERVED" x="-22.86" y="-25.4" visible="pin" length="middle"/>
</symbol>
<symbol name="MT9D111-AVX145602">
<description>MT9D111 - AVX145602‐030000‐829 connector</description>
<pin name="RESET_BAR" x="0" y="17.78" length="short" rot="R270"/>
<pin name="FRAME_VALID" x="-2.54" y="17.78" length="short" rot="R270"/>
<pin name="CLK" x="2.54" y="17.78" length="short" rot="R270"/>
<pin name="VDD" x="5.08" y="17.78" length="short" rot="R270"/>
<pin name="LINE_VALID" x="-5.08" y="17.78" length="short" rot="R270"/>
<pin name="NC6" x="-7.62" y="17.78" length="short" rot="R270"/>
<pin name="NC5" x="-10.16" y="17.78" length="short" rot="R270"/>
<pin name="PIXCLK" x="7.62" y="17.78" length="short" rot="R270"/>
<pin name="STANDBY" x="10.16" y="17.78" length="short" rot="R270"/>
<pin name="SCLK" x="12.7" y="17.78" length="short" rot="R270"/>
<pin name="SDATA" x="15.24" y="17.78" length="short" rot="R270"/>
<pin name="VDDPLL" x="-12.7" y="17.78" length="short" rot="R270"/>
<pin name="VDDQ" x="-15.24" y="17.78" length="short" rot="R270"/>
<pin name="MOTOR+" x="-17.78" y="17.78" length="short" rot="R270"/>
<pin name="FLASH" x="17.78" y="17.78" length="short" rot="R270"/>
<pin name="GND2" x="-17.78" y="-17.78" length="short" rot="R90"/>
<pin name="NC4" x="-15.24" y="-17.78" length="short" rot="R90"/>
<pin name="GPIO10" x="-12.7" y="-17.78" length="short" rot="R90"/>
<pin name="NC3" x="-10.16" y="-17.78" length="short" rot="R90"/>
<pin name="D7" x="-7.62" y="-17.78" length="short" rot="R90"/>
<pin name="D6" x="-5.08" y="-17.78" length="short" rot="R90"/>
<pin name="D5" x="-2.54" y="-17.78" length="short" rot="R90"/>
<pin name="D4" x="0" y="-17.78" length="short" rot="R90"/>
<pin name="D3" x="2.54" y="-17.78" length="short" rot="R90"/>
<pin name="D2" x="5.08" y="-17.78" length="short" rot="R90"/>
<pin name="D1" x="7.62" y="-17.78" length="short" rot="R90"/>
<pin name="D0" x="10.16" y="-17.78" length="short" rot="R90"/>
<pin name="NC2" x="12.7" y="-17.78" length="short" rot="R90"/>
<pin name="NC1" x="15.24" y="-17.78" length="short" rot="R90"/>
<pin name="GND1" x="17.78" y="-17.78" length="short" rot="R90"/>
<wire x1="20.32" y1="-15.24" x2="-20.32" y2="-15.24" width="0.254" layer="94"/>
<wire x1="-20.32" y1="-15.24" x2="-20.32" y2="15.24" width="0.254" layer="94"/>
<wire x1="-20.32" y1="15.24" x2="20.32" y2="15.24" width="0.254" layer="94"/>
<wire x1="20.32" y1="15.24" x2="20.32" y2="-15.24" width="0.254" layer="94"/>
<text x="22.86" y="12.7" size="1.27" layer="96">&gt;Value</text>
<text x="22.86" y="-15.24" size="1.27" layer="95">&gt;Name</text>
</symbol>
<symbol name="ME6211">
<description>ME6211-1.8 and ME6211-2.8 in SOT23-5 package</description>
<pin name="VIN" x="-10.16" y="5.08" length="short"/>
<pin name="VSS" x="-10.16" y="0" length="short"/>
<pin name="CE" x="-10.16" y="-5.08" length="short"/>
<pin name="VOUT" x="10.16" y="5.08" length="short" rot="R180"/>
<pin name="NC" x="10.16" y="-5.08" length="short" rot="R180"/>
<wire x1="7.62" y1="7.62" x2="7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="7.62" y1="-7.62" x2="-7.62" y2="-7.62" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-7.62" x2="-7.62" y2="7.62" width="0.254" layer="94"/>
<wire x1="-7.62" y1="7.62" x2="7.62" y2="7.62" width="0.254" layer="94"/>
<text x="-10.16" y="10.16" size="2.54" layer="96">&gt;Value</text>
<text x="-10.16" y="-12.7" size="2.54" layer="95">&gt;Name</text>
</symbol>
<symbol name="LED">
<description>LED</description>
<pin name="ANODE" x="-5.08" y="0" visible="off" length="short"/>
<pin name="CATHODE" x="5.08" y="0" visible="off" length="short" rot="R180"/>
<text x="-5.08" y="5.842" size="1.905" layer="96">&gt;Value</text>
<text x="-5.08" y="-5.08" size="1.905" layer="95">&gt;Name</text>
<wire x1="1.27" y1="-2.54" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="1.27" y2="2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="-1.27" y2="2.54" width="0.254" layer="94"/>
<wire x1="-1.27" y1="2.54" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="-1.27" y1="-2.54" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-1.27" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="-0.508" y1="3.048" x2="0.254" y2="4.318" width="0.254" layer="94"/>
<wire x1="0.508" y1="3.048" x2="1.27" y2="4.318" width="0.254" layer="94"/>
<wire x1="0" y1="4.318" x2="0.254" y2="4.318" width="0.254" layer="94"/>
<wire x1="1.016" y1="4.318" x2="1.27" y2="4.318" width="0.254" layer="94"/>
<wire x1="0.254" y1="4.318" x2="0.254" y2="4.064" width="0.254" layer="94"/>
<wire x1="1.27" y1="4.318" x2="1.27" y2="4.064" width="0.254" layer="94"/>
</symbol>
<symbol name="SAM3S8B-AU">
<description>SAM3S8B-AU in LQFP64 package</description>
<pin name="ADVREF" x="-33.02" y="17.78" length="short"/>
<pin name="GND1" x="-33.02" y="15.24" length="short"/>
<pin name="PB0" x="-33.02" y="12.7" length="short"/>
<pin name="PB1" x="-33.02" y="10.16" length="short"/>
<pin name="PB2" x="-33.02" y="7.62" length="short"/>
<pin name="PB3" x="-33.02" y="5.08" length="short"/>
<pin name="VDDIN" x="-33.02" y="2.54" length="short"/>
<pin name="VDDOUT" x="-33.02" y="0" length="short"/>
<pin name="PA17" x="-33.02" y="-2.54" length="short"/>
<pin name="PA18" x="-33.02" y="-5.08" length="short"/>
<pin name="PA21" x="-33.02" y="-7.62" length="short"/>
<pin name="VDDCORE1" x="-33.02" y="-10.16" length="short"/>
<pin name="PA19" x="-33.02" y="-12.7" length="short"/>
<pin name="PA22" x="-33.02" y="-15.24" length="short"/>
<pin name="PA23" x="-33.02" y="-17.78" length="short"/>
<pin name="PA20" x="-33.02" y="-20.32" length="short"/>
<pin name="PA0" x="33.02" y="17.78" length="short" rot="R180"/>
<pin name="PA1" x="33.02" y="15.24" length="short" rot="R180"/>
<pin name="GND3" x="33.02" y="12.7" length="short" rot="R180"/>
<pin name="VDDIO2" x="33.02" y="10.16" length="short" rot="R180"/>
<pin name="PA2" x="33.02" y="7.62" length="short" rot="R180"/>
<pin name="PA3" x="33.02" y="5.08" length="short" rot="R180"/>
<pin name="PA30" x="33.02" y="2.54" length="short" rot="R180"/>
<pin name="PA29" x="33.02" y="0" length="short" rot="R180"/>
<pin name="TST" x="33.02" y="-2.54" length="short" rot="R180"/>
<pin name="NRST" x="33.02" y="-5.08" length="short" rot="R180"/>
<pin name="PA28" x="33.02" y="-7.62" length="short" rot="R180"/>
<pin name="PA27" x="33.02" y="-10.16" length="short" rot="R180"/>
<pin name="PA4" x="33.02" y="-12.7" length="short" rot="R180"/>
<pin name="PA5" x="33.02" y="-15.24" length="short" rot="R180"/>
<pin name="PA6" x="33.02" y="-17.78" length="short" rot="R180"/>
<pin name="PB4" x="33.02" y="-20.32" length="short" rot="R180"/>
<pin name="VDDPLL" x="-17.78" y="27.94" length="short" rot="R270"/>
<pin name="PB14" x="-15.24" y="27.94" length="short" rot="R270"/>
<pin name="XIN" x="-12.7" y="27.94" length="short" rot="R270"/>
<pin name="XOUT" x="-10.16" y="27.94" length="short" rot="R270"/>
<pin name="GND4" x="-7.62" y="27.94" length="short" rot="R270"/>
<pin name="PB13" x="-5.08" y="27.94" length="short" rot="R270"/>
<pin name="PB6" x="15.24" y="27.94" length="short" rot="R270"/>
<pin name="VDDIO3" x="-2.54" y="27.94" length="short" rot="R270"/>
<pin name="PB11" x="0" y="27.94" length="short" rot="R270"/>
<pin name="PB10" x="2.54" y="27.94" length="short" rot="R270"/>
<pin name="PB12" x="5.08" y="27.94" length="short" rot="R270"/>
<pin name="VDDCORE3" x="7.62" y="27.94" length="short" rot="R270"/>
<pin name="PB7" x="10.16" y="27.94" length="short" rot="R270"/>
<pin name="PA31" x="12.7" y="27.94" length="short" rot="R270"/>
<pin name="JTAGSEL" x="17.78" y="27.94" length="short" rot="R270"/>
<pin name="PB5" x="20.32" y="27.94" length="short" rot="R270"/>
<pin name="GND2" x="-17.78" y="-30.48" length="short" rot="R90"/>
<pin name="VDDIO1" x="-15.24" y="-30.48" length="short" rot="R90"/>
<pin name="PA16" x="-12.7" y="-30.48" length="short" rot="R90"/>
<pin name="PA15" x="-10.16" y="-30.48" length="short" rot="R90"/>
<pin name="PA14" x="-7.62" y="-30.48" length="short" rot="R90"/>
<pin name="PA13" x="-5.08" y="-30.48" length="short" rot="R90"/>
<pin name="PA24" x="-2.54" y="-30.48" length="short" rot="R90"/>
<pin name="PA25" x="2.54" y="-30.48" length="short" rot="R90"/>
<pin name="VDDCORE2" x="0" y="-30.48" length="short" rot="R90"/>
<pin name="PA26" x="5.08" y="-30.48" length="short" rot="R90"/>
<pin name="PA12" x="7.62" y="-30.48" length="short" rot="R90"/>
<pin name="PA11" x="10.16" y="-30.48" length="short" rot="R90"/>
<pin name="PA10" x="12.7" y="-30.48" length="short" rot="R90"/>
<pin name="PA9" x="15.24" y="-30.48" length="short" rot="R90"/>
<pin name="PA8" x="17.78" y="-30.48" length="short" rot="R90"/>
<pin name="PA7" x="20.32" y="-30.48" length="short" rot="R90"/>
<wire x1="-30.48" y1="25.4" x2="-30.48" y2="-27.94" width="0.254" layer="94"/>
<wire x1="-30.48" y1="-27.94" x2="30.48" y2="-27.94" width="0.254" layer="94"/>
<wire x1="30.48" y1="-27.94" x2="30.48" y2="25.4" width="0.254" layer="94"/>
<wire x1="30.48" y1="25.4" x2="-30.48" y2="25.4" width="0.254" layer="94"/>
<text x="-7.62" y="5.08" size="2.54" layer="96">&gt;Value</text>
<text x="-7.62" y="-7.62" size="2.54" layer="95">&gt;Name</text>
<text x="-71.12" y="58.42" size="1.27" layer="97">1 - ADVREF
2 - GND
3 - PB0 PWMH0 AD4/RTCOUT0
4 - PB1 PWMH1 AD5/RTCOUT1
5 - PB2 URXD1 NPCS2 AD6/WKUP12
6 - PB3 UTXD1 PCK2 AD7
7 - VDDIN
8 - VDDOUT
9 - PA17 TD PCK1 PWMH3 AD0
10 - PA18 RD PCK2 A14 AD1
11 - PA21 RXD1 PCK1 AD8
12 - VDDCORE 
13 - PA19 RK PWML0 A15 AD2/WKUP9
14 - PA22 TXD1 NPCS3 NCS2 AD9
15 - PA23 SCK1 PWMH0 A19 PIODCCLK
16 - PA20 RF PWML1 A16 AD3/WKUP10</text>
<text x="-35.56" y="58.42" size="1.27" layer="97">17 - GND
18 - VDDIO
19 - PA16 TK TIOB1 PWML2 PIODCEN2 WKUP15
20 - PA15 TF TIOA1 PWML3 PIODCEN1 WKUP14
21 - PA14 SPCK PWMH3 WKUP8
22 - PA13 MOSI PWMH2
23 - PA24 RTS1 PWMH1 A20 PIODC0
24 - VDDCORE
25 - PA25 CTS1 PWMH2 A23 PIODC1
26 - PA26 DCD1 TIOA2 MCDA2 PIODC2
27 - PA12 MISO PWMH1
28 - PA11 NPCS0 PWMH0 WKUP7
29 - PA10 UTXD0 NPCS2 
30 - PA9 URXD0 NPCS1 PWMFI0 WKUP6
31 - PA8 CTS0 ADTRG WKUP5 XOUT32
32 - PA7 RTS0 PWMH3 XIN32</text>
<text x="5.08" y="58.42" size="1.27" layer="97">48 - PA0 PWMH0 TIOA0 A17 WKUP0
47 - PA1 PWMH1 TIOB0 A18 WKUP1
46 - GND
45 - VDDIO
44 - PA2 PWMH2 SCK0 DATRG WKUP2
43 - PA3 TWD0 NPCS3
42 - PA30 PWML2 NPCS2 MCDA0 PIODC6 WKUP11
41 - PA29 RI1 TCLK2 MCCK PIODC5
40 - TST
39 - NRST
38 - PA28 DSR1 TCLK1 MCCDA PIODC4
37 - PA27 DTR1 TIOB2 MCDA3 PIODC3
36 - PA4 TWCK0 TCLK0 WKUP3
35 - PA5 RXD0 NPCS3 WKUP4
34 - PA6 TXD0 PCK0 
33 - PB4 TWD1 PWMH2 TDI</text>
<text x="48.26" y="58.42" size="1.27" layer="97">64 - VDDPLL
63 - PB14 NPCS1 PWMH3 DAC1
62 - PB9 XIN
61 - PB8 XOUT
60 - GND
59 - PB13 PWML2 PCK0 DAC0
58 - VDDIO
57 - PB11 DDP
56 - PB10 DDM
55 - PB12 PWML1 ERASE
54 - VDDCORE
53 - PB7 TCK/SWCLK
52 - PA31 NPCS1 PCK2 MCDA1 PIODC7
51 - PB6 TMS/SWDIO
50 - JTAGSEL
49 - PB5 TWCK1 PWML0 WKUP13 TDO/TRACESWO</text>
</symbol>
<symbol name="CFPX-104">
<description>CFPX-104 Crystal Oscillator</description>
<wire x1="-1.27" y1="-2.54" x2="-1.27" y2="2.54" width="0.254" layer="94"/>
<wire x1="-1.27" y1="2.54" x2="1.27" y2="2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="2.54" x2="1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="-1.27" y2="-2.54" width="0.254" layer="94"/>
<wire x1="1.778" y1="-1.778" x2="1.778" y2="0" width="0.254" layer="94"/>
<wire x1="1.778" y1="0" x2="1.778" y2="1.778" width="0.254" layer="94"/>
<wire x1="-1.778" y1="1.778" x2="-1.778" y2="0" width="0.254" layer="94"/>
<wire x1="-1.778" y1="0" x2="-1.778" y2="-1.778" width="0.254" layer="94"/>
<pin name="GND2" x="-7.62" y="2.54" visible="pad" length="short"/>
<pin name="GND1" x="7.62" y="-2.54" visible="pad" length="short" rot="R180"/>
<pin name="XTAL1" x="-7.62" y="-2.54" visible="pad" length="short"/>
<pin name="XTAL2" x="7.62" y="2.54" visible="pad" length="short" rot="R180"/>
<wire x1="-1.778" y1="0" x2="-5.08" y2="0" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-5.08" y2="-2.54" width="0.254" layer="94"/>
<wire x1="1.778" y1="0" x2="5.08" y2="0" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="5.08" y2="2.54" width="0.254" layer="94"/>
<wire x1="5.08" y1="0" x2="5.08" y2="-2.54" width="0.254" layer="94"/>
<text x="-2.54" y="5.08" size="1.778" layer="95">&gt;Name</text>
<text x="-2.54" y="-7.62" size="1.778" layer="96">&gt;Value</text>
</symbol>
<symbol name="USB_MICRO_B">
<description>USB Micro-B connector</description>
<pin name="VBUS" x="-12.7" y="5.08" visible="pin" length="short"/>
<pin name="D-" x="-12.7" y="2.54" visible="pin" length="short"/>
<pin name="D+" x="-12.7" y="0" visible="pin" length="short"/>
<pin name="ID" x="-12.7" y="-2.54" visible="pin" length="short"/>
<pin name="GND" x="-12.7" y="-5.08" visible="pin" length="short"/>
<pin name="GNDH1" x="12.7" y="2.54" visible="pin" length="short" rot="R180"/>
<pin name="GNDH2" x="12.7" y="0" visible="pin" length="short" rot="R180"/>
<pin name="GNDH3" x="12.7" y="-2.54" visible="pin" length="short" rot="R180"/>
<pin name="GNDH4" x="12.7" y="-5.08" visible="pin" length="short" rot="R180"/>
<wire x1="-10.16" y1="-7.62" x2="10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="7.62" x2="-10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="-10.16" y1="7.62" x2="-10.16" y2="-7.62" width="0.254" layer="94"/>
<text x="-10.16" y="8.382" size="1.778" layer="95">&gt;Name</text>
<text x="-10.16" y="-10.16" size="1.778" layer="96">&gt;Value</text>
</symbol>
<symbol name="MCP1700">
<description>MCP1700 - SOT-23 package</description>
<pin name="GND" x="-7.62" y="2.54" visible="pin" length="short"/>
<pin name="VOUT" x="-7.62" y="-2.54" visible="pin" length="short"/>
<pin name="VIN" x="7.62" y="0" visible="pin" length="short" rot="R180"/>
<wire x1="-5.08" y1="-5.08" x2="-5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="5.08" x2="5.08" y2="5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="5.08" y1="-5.08" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<text x="-5.08" y="5.588" size="1.778" layer="95">&gt;Name</text>
<text x="-5.08" y="-7.62" size="1.778" layer="95">&gt;Value</text>
</symbol>
<symbol name="SI4060_VIAS">
<description>SI4060 with GND vias.</description>
<pin name="NC2" x="-22.86" y="0" length="short"/>
<pin name="NC1" x="-22.86" y="5.08" length="short"/>
<pin name="SDN" x="-22.86" y="10.16" length="short"/>
<pin name="TX" x="-22.86" y="-5.08" length="short"/>
<pin name="NC3" x="-22.86" y="-10.16" length="short"/>
<pin name="SDO" x="22.86" y="0" length="short" rot="R180"/>
<pin name="SDI" x="22.86" y="5.08" length="short" rot="R180"/>
<pin name="NSEL" x="22.86" y="10.16" length="short" rot="R180"/>
<pin name="SCLK" x="22.86" y="-5.08" length="short" rot="R180"/>
<pin name="NIRQ" x="22.86" y="-10.16" length="short" rot="R180"/>
<pin name="GPIO3" x="-10.16" y="22.86" length="short" rot="R270"/>
<pin name="GPIO2" x="-5.08" y="22.86" length="short" rot="R270"/>
<pin name="GND" x="0" y="22.86" length="short" rot="R270"/>
<pin name="XIN" x="5.08" y="22.86" length="short" rot="R270"/>
<pin name="XOUT" x="10.16" y="22.86" length="short" rot="R270"/>
<pin name="VDD1" x="-10.16" y="-22.86" length="short" rot="R90"/>
<pin name="TXRAMP" x="-5.08" y="-22.86" length="short" rot="R90"/>
<pin name="VDD2" x="0" y="-22.86" length="short" rot="R90"/>
<pin name="GPIO0" x="5.08" y="-22.86" length="short" rot="R90"/>
<pin name="GPIO1" x="10.16" y="-22.86" length="short" rot="R90"/>
<pin name="GNDP" x="-22.86" y="17.78" length="short"/>
<wire x1="-20.32" y1="20.32" x2="20.32" y2="20.32" width="0.254" layer="94"/>
<wire x1="20.32" y1="20.32" x2="20.32" y2="-20.32" width="0.254" layer="94"/>
<wire x1="20.32" y1="-20.32" x2="-20.32" y2="-20.32" width="0.254" layer="94"/>
<wire x1="-20.32" y1="-20.32" x2="-20.32" y2="20.32" width="0.254" layer="94"/>
<text x="-22.86" y="22.86" size="1.778" layer="95">&gt;Name</text>
<text x="-22.86" y="-25.4" size="1.778" layer="96">&gt;Value</text>
<pin name="GNDV1" x="22.86" y="-17.78" length="short" rot="R180"/>
<pin name="GNDV2" x="22.86" y="17.78" length="short" rot="R180"/>
</symbol>
<symbol name="TPS63031_VIAS">
<description>TPS63031 with GND vias.</description>
<text x="-8" y="9" size="1.27" layer="95">&gt;Name</text>
<text x="2" y="9" size="1.27" layer="96">&gt;Value</text>
<pin name="VOUT" x="-12.7" y="5.08" visible="pin" length="short"/>
<pin name="L2" x="-12.7" y="2.54" visible="pin" length="short"/>
<pin name="L1" x="-12.7" y="-2.54" visible="pin" length="short"/>
<pin name="VIN" x="-12.7" y="-5.08" visible="pin" length="short"/>
<pin name="PGND" x="-12.7" y="0" visible="pin" length="short"/>
<pin name="PAD" x="0" y="-10.16" visible="pin" length="short" rot="R90"/>
<pin name="FB" x="12.7" y="5.08" visible="pin" length="short" rot="R180"/>
<pin name="GND" x="12.7" y="2.54" visible="pin" length="short" rot="R180"/>
<pin name="VINA" x="12.7" y="0" visible="pin" length="short" rot="R180"/>
<pin name="PS/S" x="12.7" y="-2.54" visible="pin" length="short" rot="R180"/>
<pin name="EN" x="12.7" y="-5.08" visible="pin" length="short" rot="R180"/>
<wire x1="-10.16" y1="-7.62" x2="10.16" y2="-7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="-7.62" x2="10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="10.16" y1="7.62" x2="-10.16" y2="7.62" width="0.254" layer="94"/>
<wire x1="-10.16" y1="7.62" x2="-10.16" y2="-7.62" width="0.254" layer="94"/>
<pin name="VIA1" x="-2.54" y="-10.16" visible="pin" length="short" rot="R90"/>
<pin name="VIA2" x="2.54" y="-10.16" visible="pin" length="short" rot="R90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="I547-2P3_TCXO">
<description>I547-2P3-32.0000M TCXO</description>
<gates>
<gate name="G$1" symbol="I547-2P3_TCXO" x="0" y="0"/>
</gates>
<devices>
<device name="" package="I547-2P3_TCXO">
<connects>
<connect gate="G$1" pin="GND" pad="2"/>
<connect gate="G$1" pin="NC" pad="1"/>
<connect gate="G$1" pin="OUT" pad="3"/>
<connect gate="G$1" pin="VDD" pad="4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="IND0402" prefix="L">
<description>INDUCTOR 0402 - 1 x 0.5 x 0.35mm</description>
<gates>
<gate name="G$1" symbol="INDUCTOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="IND0402">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP0402" prefix="C">
<description>CAPACITOR 0402 - 1 x 0.5 x 0.35mm</description>
<gates>
<gate name="G$1" symbol="CAPACITOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CAP0402">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RES0402" prefix="R">
<description>RESISTOR 0402 - 1 x 0.5 x 0.35mm</description>
<gates>
<gate name="G$1" symbol="RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RES0402">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PAD-2.5X1.5">
<description>Pad - 2.5 x 1.5 mm</description>
<gates>
<gate name="G$1" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="PAD-2.5X1.5">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="HOLE-1.87">
<description>Hole - 1.016/1.87mm</description>
<gates>
<gate name="G$1" symbol="HOLE" x="0" y="0"/>
</gates>
<devices>
<device name="" package="HOLE-1.87">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LTC3105" prefix="U">
<description>LTC3105 MSOP-12</description>
<gates>
<gate name="G$1" symbol="LTC3105" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LTC3105">
<connects>
<connect gate="G$1" pin="!SHDN" pad="4"/>
<connect gate="G$1" pin="AUX" pad="12"/>
<connect gate="G$1" pin="FB" pad="1"/>
<connect gate="G$1" pin="FBLDO" pad="3"/>
<connect gate="G$1" pin="GND@6" pad="6"/>
<connect gate="G$1" pin="GND@7" pad="7"/>
<connect gate="G$1" pin="LDO" pad="2"/>
<connect gate="G$1" pin="MPPC" pad="5"/>
<connect gate="G$1" pin="PGOOD" pad="10"/>
<connect gate="G$1" pin="SW" pad="9"/>
<connect gate="G$1" pin="VIN" pad="8"/>
<connect gate="G$1" pin="VOUT" pad="11"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DLJ4018" prefix="L">
<description>FERROCORE DLJ4018-10uH</description>
<gates>
<gate name="G$1" symbol="INDUCTOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DLJ4018">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP0805" prefix="C">
<description>CAPACITOR 0805 - 2.0 x 1.2 x 0.45mm</description>
<gates>
<gate name="G$1" symbol="CAPACITOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CAP0805">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CAP0603" prefix="C">
<description>CAPACITOR 0603 - 1.55 x 0.85 x 0.45mm</description>
<gates>
<gate name="G$1" symbol="CAPACITOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CAP0603">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="DLJ3015" prefix="L">
<description>FERROCORE DLJ3015-2.2</description>
<gates>
<gate name="G$1" symbol="INDUCTOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="DLJ3015">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="UBLOX_MAX-7C">
<description>UBLOX MAX</description>
<gates>
<gate name="G$1" symbol="UBLOX_MAX-7C" x="-2.54" y="7.62"/>
</gates>
<devices>
<device name="" package="UBLOX_MAX-7C">
<connects>
<connect gate="G$1" pin="10_GND" pad="10_GND"/>
<connect gate="G$1" pin="11_RF_IN" pad="11_RF_IN"/>
<connect gate="G$1" pin="12_GND" pad="12_GND"/>
<connect gate="G$1" pin="13_ANTON" pad="13_ANTON"/>
<connect gate="G$1" pin="14_VCC_RF" pad="14_VCC_RF"/>
<connect gate="G$1" pin="15_RESERVED" pad="15_RESERVED"/>
<connect gate="G$1" pin="16_SDA2" pad="16_SDA2"/>
<connect gate="G$1" pin="17_SCL2" pad="17_SCL2"/>
<connect gate="G$1" pin="18_RESERVED" pad="18_RESERVED"/>
<connect gate="G$1" pin="1_GND" pad="1_GND"/>
<connect gate="G$1" pin="2_TXD1" pad="2_TXD1"/>
<connect gate="G$1" pin="3_RXD1" pad="3_RXD1"/>
<connect gate="G$1" pin="4_TIMEPULSE" pad="4_TIMEPULSE"/>
<connect gate="G$1" pin="5_EXTINT0" pad="5_EXTINT0"/>
<connect gate="G$1" pin="6_V_BCKP" pad="6_V_BCKP"/>
<connect gate="G$1" pin="7_VCC_IO" pad="7_VCC_IO"/>
<connect gate="G$1" pin="8_VCC" pad="8_VCC"/>
<connect gate="G$1" pin="9_V_RESET" pad="9_V_RESET"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="RES0603" prefix="R">
<description>RESISTOR 0603 - 1.55 x 0.85 x 0.45mm</description>
<gates>
<gate name="G$1" symbol="RESISTOR" x="0" y="0"/>
</gates>
<devices>
<device name="" package="RES0603">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
<connect gate="G$1" pin="P$2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="LED0603">
<description>LED 0603</description>
<gates>
<gate name="G$1" symbol="LED" x="0" y="0"/>
</gates>
<devices>
<device name="" package="LED0603">
<connects>
<connect gate="G$1" pin="ANODE" pad="ANODE"/>
<connect gate="G$1" pin="CATHODE" pad="CATHODE"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SAM3S8B-AU" prefix="U">
<description>SAM3S8B-AU</description>
<gates>
<gate name="G$1" symbol="SAM3S8B-AU" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SAM3S8B-AU">
<connects>
<connect gate="G$1" pin="ADVREF" pad="1"/>
<connect gate="G$1" pin="GND1" pad="2"/>
<connect gate="G$1" pin="GND2" pad="17"/>
<connect gate="G$1" pin="GND3" pad="46"/>
<connect gate="G$1" pin="GND4" pad="60"/>
<connect gate="G$1" pin="JTAGSEL" pad="50"/>
<connect gate="G$1" pin="NRST" pad="39"/>
<connect gate="G$1" pin="PA0" pad="48"/>
<connect gate="G$1" pin="PA1" pad="47"/>
<connect gate="G$1" pin="PA10" pad="29"/>
<connect gate="G$1" pin="PA11" pad="28"/>
<connect gate="G$1" pin="PA12" pad="27"/>
<connect gate="G$1" pin="PA13" pad="22"/>
<connect gate="G$1" pin="PA14" pad="21"/>
<connect gate="G$1" pin="PA15" pad="20"/>
<connect gate="G$1" pin="PA16" pad="19"/>
<connect gate="G$1" pin="PA17" pad="9"/>
<connect gate="G$1" pin="PA18" pad="10"/>
<connect gate="G$1" pin="PA19" pad="13"/>
<connect gate="G$1" pin="PA2" pad="44"/>
<connect gate="G$1" pin="PA20" pad="16"/>
<connect gate="G$1" pin="PA21" pad="11"/>
<connect gate="G$1" pin="PA22" pad="14"/>
<connect gate="G$1" pin="PA23" pad="15"/>
<connect gate="G$1" pin="PA24" pad="23"/>
<connect gate="G$1" pin="PA25" pad="25"/>
<connect gate="G$1" pin="PA26" pad="26"/>
<connect gate="G$1" pin="PA27" pad="37"/>
<connect gate="G$1" pin="PA28" pad="38"/>
<connect gate="G$1" pin="PA29" pad="41"/>
<connect gate="G$1" pin="PA3" pad="43"/>
<connect gate="G$1" pin="PA30" pad="42"/>
<connect gate="G$1" pin="PA31" pad="52"/>
<connect gate="G$1" pin="PA4" pad="36"/>
<connect gate="G$1" pin="PA5" pad="35"/>
<connect gate="G$1" pin="PA6" pad="34"/>
<connect gate="G$1" pin="PA7" pad="32"/>
<connect gate="G$1" pin="PA8" pad="31"/>
<connect gate="G$1" pin="PA9" pad="30"/>
<connect gate="G$1" pin="PB0" pad="3"/>
<connect gate="G$1" pin="PB1" pad="4"/>
<connect gate="G$1" pin="PB10" pad="56"/>
<connect gate="G$1" pin="PB11" pad="57"/>
<connect gate="G$1" pin="PB12" pad="55"/>
<connect gate="G$1" pin="PB13" pad="59"/>
<connect gate="G$1" pin="PB14" pad="63"/>
<connect gate="G$1" pin="PB2" pad="5"/>
<connect gate="G$1" pin="PB3" pad="6"/>
<connect gate="G$1" pin="PB4" pad="33"/>
<connect gate="G$1" pin="PB5" pad="49"/>
<connect gate="G$1" pin="PB6" pad="51"/>
<connect gate="G$1" pin="PB7" pad="53"/>
<connect gate="G$1" pin="TST" pad="40"/>
<connect gate="G$1" pin="VDDCORE1" pad="12"/>
<connect gate="G$1" pin="VDDCORE2" pad="24"/>
<connect gate="G$1" pin="VDDCORE3" pad="54"/>
<connect gate="G$1" pin="VDDIN" pad="7"/>
<connect gate="G$1" pin="VDDIO1" pad="18"/>
<connect gate="G$1" pin="VDDIO2" pad="45"/>
<connect gate="G$1" pin="VDDIO3" pad="58"/>
<connect gate="G$1" pin="VDDOUT" pad="8"/>
<connect gate="G$1" pin="VDDPLL" pad="64"/>
<connect gate="G$1" pin="XIN" pad="62"/>
<connect gate="G$1" pin="XOUT" pad="61"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CFPX-104">
<description>CFPX-104 Crystal Oscillator</description>
<gates>
<gate name="G$1" symbol="CFPX-104" x="0" y="0"/>
</gates>
<devices>
<device name="" package="CFPX-104">
<connects>
<connect gate="G$1" pin="GND1" pad="2"/>
<connect gate="G$1" pin="GND2" pad="4"/>
<connect gate="G$1" pin="XTAL1" pad="1"/>
<connect gate="G$1" pin="XTAL2" pad="3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="USB_MICRO_B">
<description>USB Micro-B connector</description>
<gates>
<gate name="G$1" symbol="USB_MICRO_B" x="0" y="0"/>
</gates>
<devices>
<device name="" package="USB_MICRO_B">
<connects>
<connect gate="G$1" pin="D+" pad="D+"/>
<connect gate="G$1" pin="D-" pad="D-"/>
<connect gate="G$1" pin="GND" pad="GND"/>
<connect gate="G$1" pin="GNDH1" pad="P$6"/>
<connect gate="G$1" pin="GNDH2" pad="P$7"/>
<connect gate="G$1" pin="GNDH3" pad="P$8"/>
<connect gate="G$1" pin="GNDH4" pad="P$9"/>
<connect gate="G$1" pin="ID" pad="ID"/>
<connect gate="G$1" pin="VBUS" pad="VBUS"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MCP1700">
<description>MCP1700 - SOT-23 package</description>
<gates>
<gate name="G$1" symbol="MCP1700" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MCP1700">
<connects>
<connect gate="G$1" pin="GND" pad="1"/>
<connect gate="G$1" pin="VIN" pad="3"/>
<connect gate="G$1" pin="VOUT" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="PAD-3X1.5">
<description>Pad - 3 x 1.5 mm</description>
<gates>
<gate name="G$1" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="PAD-3X1.5">
<connects>
<connect gate="G$1" pin="P$1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MT9D111-AVX145602-NEW">
<description>MT9D111-AVX145602 connector with pads closer to each other</description>
<gates>
<gate name="G$1" symbol="MT9D111-AVX145602" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MT9D111-AVX145602-NEW">
<connects>
<connect gate="G$1" pin="CLK" pad="24"/>
<connect gate="G$1" pin="D0" pad="4"/>
<connect gate="G$1" pin="D1" pad="5"/>
<connect gate="G$1" pin="D2" pad="6"/>
<connect gate="G$1" pin="D3" pad="7"/>
<connect gate="G$1" pin="D4" pad="8"/>
<connect gate="G$1" pin="D5" pad="9"/>
<connect gate="G$1" pin="D6" pad="10"/>
<connect gate="G$1" pin="D7" pad="11"/>
<connect gate="G$1" pin="FLASH" pad="30"/>
<connect gate="G$1" pin="FRAME_VALID" pad="22"/>
<connect gate="G$1" pin="GND1" pad="1"/>
<connect gate="G$1" pin="GND2" pad="15"/>
<connect gate="G$1" pin="GPIO10" pad="13"/>
<connect gate="G$1" pin="LINE_VALID" pad="21"/>
<connect gate="G$1" pin="MOTOR+" pad="16"/>
<connect gate="G$1" pin="NC1" pad="2"/>
<connect gate="G$1" pin="NC2" pad="3"/>
<connect gate="G$1" pin="NC3" pad="12"/>
<connect gate="G$1" pin="NC4" pad="14"/>
<connect gate="G$1" pin="NC5" pad="19"/>
<connect gate="G$1" pin="NC6" pad="20"/>
<connect gate="G$1" pin="PIXCLK" pad="26"/>
<connect gate="G$1" pin="RESET_BAR" pad="23"/>
<connect gate="G$1" pin="SCLK" pad="28"/>
<connect gate="G$1" pin="SDATA" pad="29"/>
<connect gate="G$1" pin="STANDBY" pad="27"/>
<connect gate="G$1" pin="VDD" pad="25"/>
<connect gate="G$1" pin="VDDPLL" pad="18"/>
<connect gate="G$1" pin="VDDQ" pad="17"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="SI4060_VIAS">
<description>SI4060 with GND vias.</description>
<gates>
<gate name="G$1" symbol="SI4060_VIAS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SI4060_VIAS">
<connects>
<connect gate="G$1" pin="GND" pad="P18"/>
<connect gate="G$1" pin="GNDP" pad="GNDP"/>
<connect gate="G$1" pin="GNDV1" pad="GNDV1"/>
<connect gate="G$1" pin="GNDV2" pad="GNDV2"/>
<connect gate="G$1" pin="GPIO0" pad="P9"/>
<connect gate="G$1" pin="GPIO1" pad="P10"/>
<connect gate="G$1" pin="GPIO2" pad="P19"/>
<connect gate="G$1" pin="GPIO3" pad="P20"/>
<connect gate="G$1" pin="NC1" pad="P2"/>
<connect gate="G$1" pin="NC2" pad="P3"/>
<connect gate="G$1" pin="NC3" pad="P5"/>
<connect gate="G$1" pin="NIRQ" pad="P11"/>
<connect gate="G$1" pin="NSEL" pad="P15"/>
<connect gate="G$1" pin="SCLK" pad="P12"/>
<connect gate="G$1" pin="SDI" pad="P14"/>
<connect gate="G$1" pin="SDN" pad="P1"/>
<connect gate="G$1" pin="SDO" pad="P13"/>
<connect gate="G$1" pin="TX" pad="P4"/>
<connect gate="G$1" pin="TXRAMP" pad="P7"/>
<connect gate="G$1" pin="VDD1" pad="P6"/>
<connect gate="G$1" pin="VDD2" pad="P8"/>
<connect gate="G$1" pin="XIN" pad="P17"/>
<connect gate="G$1" pin="XOUT" pad="P16"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="TPS63031_VIAS" prefix="U">
<description>TPS63031</description>
<gates>
<gate name="G$1" symbol="TPS63031_VIAS" x="0" y="0"/>
</gates>
<devices>
<device name="" package="TPS63031_VIAS">
<connects>
<connect gate="G$1" pin="EN" pad="6"/>
<connect gate="G$1" pin="FB" pad="10"/>
<connect gate="G$1" pin="GND" pad="9"/>
<connect gate="G$1" pin="L1" pad="4"/>
<connect gate="G$1" pin="L2" pad="2"/>
<connect gate="G$1" pin="PAD" pad="11"/>
<connect gate="G$1" pin="PGND" pad="3"/>
<connect gate="G$1" pin="PS/S" pad="7"/>
<connect gate="G$1" pin="VIA1" pad="VIA1"/>
<connect gate="G$1" pin="VIA2" pad="VIA2"/>
<connect gate="G$1" pin="VIN" pad="5"/>
<connect gate="G$1" pin="VINA" pad="8"/>
<connect gate="G$1" pin="VOUT" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="ME6211_NEW" prefix="U">
<description>ME6211-1.8 and ME6211-2.8 in SOT23-5 package without silkscreen.</description>
<gates>
<gate name="G$1" symbol="ME6211" x="0" y="0"/>
</gates>
<devices>
<device name="" package="ME6211_NEW">
<connects>
<connect gate="G$1" pin="CE" pad="3"/>
<connect gate="G$1" pin="NC" pad="4"/>
<connect gate="G$1" pin="VIN" pad="1"/>
<connect gate="G$1" pin="VOUT" pad="5"/>
<connect gate="G$1" pin="VSS" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply2">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
Please keep in mind, that these devices are necessary for the
automatic wiring of the supply signals.&lt;p&gt;
The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<text x="-1.905" y="-3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="SUPPLY">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="GND" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="SparkFun-Connectors">
<description>&lt;h3&gt;SparkFun Electronics' preferred foot prints&lt;/h3&gt;
In this library you'll find connectors and sockets- basically anything that can be plugged into or onto.&lt;br&gt;&lt;br&gt;
We've spent an enormous amount of time creating and checking these footprints and parts, but it is the end user's responsibility to ensure correctness and suitablity for a given componet or application. If you enjoy using this library, please buy one of our products at www.sparkfun.com.
&lt;br&gt;&lt;br&gt;
&lt;b&gt;Licensing:&lt;/b&gt; Creative Commons ShareAlike 4.0 International - https://creativecommons.org/licenses/by-sa/4.0/ 
&lt;br&gt;&lt;br&gt;
You are welcome to use this library for commercial purposes. For attribution, we ask that when you begin to sell your device using our footprint, you email us with a link to the product being sold. We want bragging rights that we helped (in a very small part) to create your 8th world wonder. We would like the opportunity to feature your device on our homepage.</description>
<packages>
<package name="1X02">
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.635" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="MOLEX-1X2">
<wire x1="-1.27" y1="3.048" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="3.81" y1="3.048" x2="3.81" y2="-2.54" width="0.127" layer="21"/>
<wire x1="3.81" y1="3.048" x2="-1.27" y2="3.048" width="0.127" layer="21"/>
<wire x1="3.81" y1="-2.54" x2="2.54" y2="-2.54" width="0.127" layer="21"/>
<wire x1="2.54" y1="-2.54" x2="0" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0" y1="-1.27" x2="2.54" y2="-1.27" width="0.127" layer="21"/>
<wire x1="2.54" y1="-1.27" x2="2.54" y2="-2.54" width="0.127" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" shape="square"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796"/>
</package>
<package name="SCREWTERMINAL-3.5MM-2">
<circle x="2" y="3" radius="0.2828" width="0.127" layer="51"/>
<wire x1="-1.75" y1="3.4" x2="5.25" y2="3.4" width="0.2032" layer="21"/>
<wire x1="5.25" y1="3.4" x2="5.25" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="5.25" y1="-2.8" x2="5.25" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="5.25" y1="-3.6" x2="-1.75" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="-1.75" y1="-3.6" x2="-1.75" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-1.75" y1="-2.8" x2="-1.75" y2="3.4" width="0.2032" layer="21"/>
<wire x1="5.25" y1="-2.8" x2="-1.75" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-1.75" y1="-1.35" x2="-2.25" y2="-1.35" width="0.2032" layer="51"/>
<wire x1="-2.25" y1="-1.35" x2="-2.25" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="-2.25" y1="-2.35" x2="-1.75" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="5.25" y1="3.15" x2="5.75" y2="3.15" width="0.2032" layer="51"/>
<wire x1="5.75" y1="3.15" x2="5.75" y2="2.15" width="0.2032" layer="51"/>
<wire x1="5.75" y1="2.15" x2="5.25" y2="2.15" width="0.2032" layer="51"/>
<pad name="1" x="0" y="0" drill="1.2" diameter="2.032" shape="square"/>
<pad name="2" x="3.5" y="0" drill="1.2" diameter="2.032"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="1.27" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="JST-2-SMD">
<description>2mm SMD side-entry connector. tDocu layer indicates the actual physical plastic housing. +/- indicate SparkFun standard batteries and wiring.</description>
<wire x1="-4" y1="-1" x2="-4" y2="-4.5" width="0.2032" layer="21"/>
<wire x1="-4" y1="-4.5" x2="-3.2" y2="-4.5" width="0.2032" layer="21"/>
<wire x1="-3.2" y1="-4.5" x2="-3.2" y2="-2" width="0.2032" layer="21"/>
<wire x1="-3.2" y1="-2" x2="-2" y2="-2" width="0.2032" layer="21"/>
<wire x1="2" y1="-2" x2="3.2" y2="-2" width="0.2032" layer="21"/>
<wire x1="3.2" y1="-2" x2="3.2" y2="-4.5" width="0.2032" layer="21"/>
<wire x1="3.2" y1="-4.5" x2="4" y2="-4.5" width="0.2032" layer="21"/>
<wire x1="4" y1="-4.5" x2="4" y2="-1" width="0.2032" layer="21"/>
<wire x1="2" y1="3" x2="-2" y2="3" width="0.2032" layer="21"/>
<smd name="1" x="-1" y="-3.7" dx="1" dy="4.6" layer="1"/>
<smd name="2" x="1" y="-3.7" dx="1" dy="4.6" layer="1"/>
<smd name="NC1" x="-3.4" y="1.5" dx="3.4" dy="1.6" layer="1" rot="R90"/>
<smd name="NC2" x="3.4" y="1.5" dx="3.4" dy="1.6" layer="1" rot="R90"/>
<text x="-1.27" y="1.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="0" size="0.4064" layer="27">&gt;Value</text>
</package>
<package name="1X02_BIG">
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.127" layer="21"/>
<wire x1="-1.27" y1="-1.27" x2="5.08" y2="-1.27" width="0.127" layer="21"/>
<wire x1="5.08" y1="-1.27" x2="5.08" y2="1.27" width="0.127" layer="21"/>
<wire x1="5.08" y1="1.27" x2="-1.27" y2="1.27" width="0.127" layer="21"/>
<pad name="P$1" x="0" y="0" drill="1.0668"/>
<pad name="P$2" x="3.81" y="0" drill="1.0668"/>
</package>
<package name="JST-2-SMD-VERT">
<wire x1="-4.1" y1="2.97" x2="4.2" y2="2.97" width="0.2032" layer="51"/>
<wire x1="4.2" y1="2.97" x2="4.2" y2="-2.13" width="0.2032" layer="51"/>
<wire x1="4.2" y1="-2.13" x2="-4.1" y2="-2.13" width="0.2032" layer="51"/>
<wire x1="-4.1" y1="-2.13" x2="-4.1" y2="2.97" width="0.2032" layer="51"/>
<wire x1="-4.1" y1="3" x2="4.2" y2="3" width="0.2032" layer="21"/>
<wire x1="4.2" y1="3" x2="4.2" y2="2.3" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="3" x2="-4.1" y2="2.3" width="0.2032" layer="21"/>
<wire x1="2" y1="-2.1" x2="4.2" y2="-2.1" width="0.2032" layer="21"/>
<wire x1="4.2" y1="-2.1" x2="4.2" y2="-1.7" width="0.2032" layer="21"/>
<wire x1="-2" y1="-2.1" x2="-4.1" y2="-2.1" width="0.2032" layer="21"/>
<wire x1="-4.1" y1="-2.1" x2="-4.1" y2="-1.8" width="0.2032" layer="21"/>
<smd name="P$1" x="-3.4" y="0.27" dx="3" dy="1.6" layer="1" rot="R90"/>
<smd name="P$2" x="3.4" y="0.27" dx="3" dy="1.6" layer="1" rot="R90"/>
<smd name="VCC" x="-1" y="-2" dx="1" dy="5.5" layer="1"/>
<smd name="GND" x="1" y="-2" dx="1" dy="5.5" layer="1"/>
<text x="2.54" y="-5.08" size="1.27" layer="25">&gt;Name</text>
<text x="2.24" y="3.48" size="1.27" layer="27">&gt;Value</text>
</package>
<package name="R_SW_TH">
<wire x1="-1.651" y1="19.2532" x2="-1.651" y2="-1.3716" width="0.2032" layer="21"/>
<wire x1="-1.651" y1="-1.3716" x2="-1.651" y2="-2.2352" width="0.2032" layer="21"/>
<wire x1="-1.651" y1="19.2532" x2="13.589" y2="19.2532" width="0.2032" layer="21"/>
<wire x1="13.589" y1="19.2532" x2="13.589" y2="-2.2352" width="0.2032" layer="21"/>
<wire x1="13.589" y1="-2.2352" x2="-1.651" y2="-2.2352" width="0.2032" layer="21"/>
<pad name="P$1" x="0" y="0" drill="1.6002"/>
<pad name="P$2" x="0" y="16.9926" drill="1.6002"/>
<pad name="P$3" x="12.0904" y="15.494" drill="1.6002"/>
<pad name="P$4" x="12.0904" y="8.4582" drill="1.6002"/>
</package>
<package name="SCREWTERMINAL-5MM-2">
<wire x1="-3.1" y1="4.2" x2="8.1" y2="4.2" width="0.2032" layer="21"/>
<wire x1="8.1" y1="4.2" x2="8.1" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="8.1" y1="-2.3" x2="8.1" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="8.1" y1="-3.3" x2="-3.1" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="-3.3" x2="-3.1" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="-2.3" x2="-3.1" y2="4.2" width="0.2032" layer="21"/>
<wire x1="8.1" y1="-2.3" x2="-3.1" y2="-2.3" width="0.2032" layer="21"/>
<wire x1="-3.1" y1="-1.35" x2="-3.7" y2="-1.35" width="0.2032" layer="51"/>
<wire x1="-3.7" y1="-1.35" x2="-3.7" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="-3.7" y1="-2.35" x2="-3.1" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="8.1" y1="4" x2="8.7" y2="4" width="0.2032" layer="51"/>
<wire x1="8.7" y1="4" x2="8.7" y2="3" width="0.2032" layer="51"/>
<wire x1="8.7" y1="3" x2="8.1" y2="3" width="0.2032" layer="51"/>
<circle x="2.5" y="3.7" radius="0.2828" width="0.127" layer="51"/>
<pad name="1" x="0" y="0" drill="1.3" diameter="2.032" shape="square"/>
<pad name="2" x="5" y="0" drill="1.3" diameter="2.032"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="1.27" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X02_LOCK">
<wire x1="-0.635" y1="1.27" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.905" y2="1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="1.27" x2="3.175" y2="1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="1.27" x2="3.81" y2="0.635" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.635" x2="3.175" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.175" y1="-1.27" x2="1.905" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.635" x2="3.81" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="-0.1778" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.7178" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.2921" y1="-0.2921" x2="0.2921" y2="0.2921" layer="51"/>
<rectangle x1="2.2479" y1="-0.2921" x2="2.8321" y2="0.2921" layer="51"/>
</package>
<package name="MOLEX-1X2_LOCK">
<wire x1="-1.27" y1="3.048" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="3.81" y1="3.048" x2="3.81" y2="-2.54" width="0.127" layer="21"/>
<wire x1="3.81" y1="3.048" x2="-1.27" y2="3.048" width="0.127" layer="21"/>
<wire x1="3.81" y1="-2.54" x2="2.54" y2="-2.54" width="0.127" layer="21"/>
<wire x1="2.54" y1="-2.54" x2="0" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="-1.27" y2="-2.54" width="0.127" layer="21"/>
<wire x1="0" y1="-2.54" x2="0" y2="-1.27" width="0.127" layer="21"/>
<wire x1="0" y1="-1.27" x2="2.54" y2="-1.27" width="0.127" layer="21"/>
<wire x1="2.54" y1="-1.27" x2="2.54" y2="-2.54" width="0.127" layer="21"/>
<pad name="1" x="-0.127" y="0" drill="1.016" diameter="1.8796" shape="square"/>
<pad name="2" x="2.667" y="0" drill="1.016" diameter="1.8796"/>
<rectangle x1="-0.2921" y1="-0.2921" x2="0.2921" y2="0.2921" layer="51"/>
<rectangle x1="2.2479" y1="-0.2921" x2="2.8321" y2="0.2921" layer="51"/>
</package>
<package name="1X02_LOCK_LONGPADS">
<description>This footprint was designed to help hold the alignment of a through-hole component (i.e.  6-pin header) while soldering it into place.  
You may notice that each hole has been shifted either up or down by 0.005 of an inch from it's more standard position (which is a perfectly straight line).  
This slight alteration caused the pins (the squares in the middle) to touch the edges of the holes.  Because they are alternating, it causes a "brace" 
to hold the component in place.  0.005 has proven to be the perfect amount of "off-center" position when using our standard breakaway headers.
Although looks a little odd when you look at the bare footprint, once you have a header in there, the alteration is very hard to notice.  Also,
if you push a header all the way into place, it is covered up entirely on the bottom side.  This idea of altering the position of holes to aid alignment 
will be further integrated into the Sparkfun Library for other footprints.  It can help hold any component with 3 or more connection pins.</description>
<wire x1="1.651" y1="0" x2="0.889" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0" x2="-1.016" y2="0" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="0.9906" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.9906" x2="-0.9906" y2="1.27" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0" x2="-1.27" y2="-0.9906" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.9906" x2="-0.9906" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0" x2="3.556" y2="0" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0" x2="3.81" y2="-0.9906" width="0.2032" layer="21"/>
<wire x1="3.81" y1="-0.9906" x2="3.5306" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0" x2="3.81" y2="0.9906" width="0.2032" layer="21"/>
<wire x1="3.81" y1="0.9906" x2="3.5306" y2="1.27" width="0.2032" layer="21"/>
<pad name="1" x="-0.127" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="2.667" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-1.27" y="1.778" size="1.27" layer="25" font="vector">&gt;NAME</text>
<text x="-1.27" y="-3.302" size="1.27" layer="27" font="vector">&gt;VALUE</text>
<rectangle x1="-0.2921" y1="-0.2921" x2="0.2921" y2="0.2921" layer="51"/>
<rectangle x1="2.2479" y1="-0.2921" x2="2.8321" y2="0.2921" layer="51"/>
</package>
<package name="SCREWTERMINAL-3.5MM-2_LOCK">
<wire x1="-1.75" y1="3.4" x2="5.25" y2="3.4" width="0.2032" layer="21"/>
<wire x1="5.25" y1="3.4" x2="5.25" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="5.25" y1="-2.8" x2="5.25" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="5.25" y1="-3.6" x2="-1.75" y2="-3.6" width="0.2032" layer="21"/>
<wire x1="-1.75" y1="-3.6" x2="-1.75" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-1.75" y1="-2.8" x2="-1.75" y2="3.4" width="0.2032" layer="21"/>
<wire x1="5.25" y1="-2.8" x2="-1.75" y2="-2.8" width="0.2032" layer="21"/>
<wire x1="-1.75" y1="-1.35" x2="-2.15" y2="-1.35" width="0.2032" layer="51"/>
<wire x1="-2.15" y1="-1.35" x2="-2.15" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="-2.15" y1="-2.35" x2="-1.75" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="5.25" y1="3.15" x2="5.65" y2="3.15" width="0.2032" layer="51"/>
<wire x1="5.65" y1="3.15" x2="5.65" y2="2.15" width="0.2032" layer="51"/>
<wire x1="5.65" y1="2.15" x2="5.25" y2="2.15" width="0.2032" layer="51"/>
<circle x="2" y="3" radius="0.2828" width="0.127" layer="51"/>
<circle x="0" y="0" radius="0.4318" width="0.0254" layer="51"/>
<circle x="3.5" y="0" radius="0.4318" width="0.0254" layer="51"/>
<pad name="1" x="-0.1778" y="0" drill="1.2" diameter="2.032" shape="square"/>
<pad name="2" x="3.6778" y="0" drill="1.2" diameter="2.032"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="1.27" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="1X02_LONGPADS">
<pad name="1" x="0" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
</package>
<package name="1X02_NO_SILK">
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="2.286" y1="-0.254" x2="2.794" y2="0.254" layer="51"/>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="JST-2-PTH">
<pad name="1" x="-1" y="0" drill="0.7" diameter="1.6"/>
<pad name="2" x="1" y="0" drill="0.7" diameter="1.6"/>
<text x="-1.27" y="5.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="4" size="0.4064" layer="27">&gt;Value</text>
<text x="0.6" y="0.7" size="1.27" layer="51">+</text>
<text x="-1.4" y="0.7" size="1.27" layer="51">-</text>
<wire x1="-2.95" y1="-1.6" x2="-2.95" y2="6" width="0.2032" layer="21"/>
<wire x1="-2.95" y1="6" x2="2.95" y2="6" width="0.2032" layer="21"/>
<wire x1="2.95" y1="6" x2="2.95" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.95" y1="-1.6" x2="-2.3" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="2.95" y1="-1.6" x2="2.3" y2="-1.6" width="0.2032" layer="21"/>
<wire x1="-2.3" y1="-1.6" x2="-2.3" y2="0" width="0.2032" layer="21"/>
<wire x1="2.3" y1="-1.6" x2="2.3" y2="0" width="0.2032" layer="21"/>
</package>
<package name="1X02_XTRA_BIG">
<wire x1="-5.08" y1="2.54" x2="-5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="-5.08" y1="-2.54" x2="5.08" y2="-2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="-2.54" x2="5.08" y2="2.54" width="0.127" layer="21"/>
<wire x1="5.08" y1="2.54" x2="-5.08" y2="2.54" width="0.127" layer="21"/>
<pad name="1" x="-2.54" y="0" drill="2.0574" diameter="3.556"/>
<pad name="2" x="2.54" y="0" drill="2.0574" diameter="3.556"/>
</package>
<package name="1X02_PP_HOLES_ONLY">
<circle x="0" y="0" radius="0.635" width="0.127" layer="51"/>
<circle x="2.54" y="0" radius="0.635" width="0.127" layer="51"/>
<pad name="1" x="0" y="0" drill="0.889" diameter="0.8128" rot="R90"/>
<pad name="2" x="2.54" y="0" drill="0.889" diameter="0.8128" rot="R90"/>
<hole x="0" y="0" drill="1.4732"/>
<hole x="2.54" y="0" drill="1.4732"/>
</package>
<package name="SCREWTERMINAL-3.5MM-2-NS">
<wire x1="-1.75" y1="3.4" x2="5.25" y2="3.4" width="0.2032" layer="51"/>
<wire x1="5.25" y1="3.4" x2="5.25" y2="-2.8" width="0.2032" layer="51"/>
<wire x1="5.25" y1="-2.8" x2="5.25" y2="-3.6" width="0.2032" layer="51"/>
<wire x1="5.25" y1="-3.6" x2="-1.75" y2="-3.6" width="0.2032" layer="51"/>
<wire x1="-1.75" y1="-3.6" x2="-1.75" y2="-2.8" width="0.2032" layer="51"/>
<wire x1="-1.75" y1="-2.8" x2="-1.75" y2="3.4" width="0.2032" layer="51"/>
<wire x1="5.25" y1="-2.8" x2="-1.75" y2="-2.8" width="0.2032" layer="51"/>
<wire x1="-1.75" y1="-1.35" x2="-2.15" y2="-1.35" width="0.2032" layer="51"/>
<wire x1="-2.15" y1="-1.35" x2="-2.15" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="-2.15" y1="-2.35" x2="-1.75" y2="-2.35" width="0.2032" layer="51"/>
<wire x1="5.25" y1="3.15" x2="5.65" y2="3.15" width="0.2032" layer="51"/>
<wire x1="5.65" y1="3.15" x2="5.65" y2="2.15" width="0.2032" layer="51"/>
<wire x1="5.65" y1="2.15" x2="5.25" y2="2.15" width="0.2032" layer="51"/>
<circle x="2" y="3" radius="0.2828" width="0.127" layer="51"/>
<pad name="1" x="0" y="0" drill="1.2" diameter="2.032" shape="square"/>
<pad name="2" x="3.5" y="0" drill="1.2" diameter="2.032"/>
<text x="-1.27" y="2.54" size="0.4064" layer="25">&gt;NAME</text>
<text x="-1.27" y="1.27" size="0.4064" layer="27">&gt;VALUE</text>
</package>
<package name="JST-2-PTH-NS">
<wire x1="-2" y1="0" x2="-2" y2="-1.8" width="0.2032" layer="51"/>
<wire x1="-2" y1="-1.8" x2="-3" y2="-1.8" width="0.2032" layer="51"/>
<wire x1="-3" y1="-1.8" x2="-3" y2="6" width="0.2032" layer="51"/>
<wire x1="-3" y1="6" x2="3" y2="6" width="0.2032" layer="51"/>
<wire x1="3" y1="6" x2="3" y2="-1.8" width="0.2032" layer="51"/>
<wire x1="3" y1="-1.8" x2="2" y2="-1.8" width="0.2032" layer="51"/>
<wire x1="2" y1="-1.8" x2="2" y2="0" width="0.2032" layer="51"/>
<pad name="1" x="-1" y="0" drill="0.7" diameter="1.6"/>
<pad name="2" x="1" y="0" drill="0.7" diameter="1.6"/>
<text x="-1.27" y="5.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="4" size="0.4064" layer="27">&gt;Value</text>
<text x="0.6" y="0.7" size="1.27" layer="51">+</text>
<text x="-1.4" y="0.7" size="1.27" layer="51">-</text>
</package>
<package name="JST-2-PTH-KIT">
<description>&lt;H3&gt;JST-2-PTH-KIT&lt;/h3&gt;
2-Pin JST, through-hole connector&lt;br&gt;
&lt;br&gt;
&lt;b&gt;Warning:&lt;/b&gt; This is the KIT version of this package. This package has a smaller diameter top stop mask, which doesn't cover the diameter of the pad. This means only the bottom side of the pads' copper will be exposed. You'll only be able to solder to the bottom side.</description>
<wire x1="-2" y1="0" x2="-2" y2="-1.8" width="0.2032" layer="51"/>
<wire x1="-2" y1="-1.8" x2="-3" y2="-1.8" width="0.2032" layer="51"/>
<wire x1="-3" y1="-1.8" x2="-3" y2="6" width="0.2032" layer="51"/>
<wire x1="-3" y1="6" x2="3" y2="6" width="0.2032" layer="51"/>
<wire x1="3" y1="6" x2="3" y2="-1.8" width="0.2032" layer="51"/>
<wire x1="3" y1="-1.8" x2="2" y2="-1.8" width="0.2032" layer="51"/>
<wire x1="2" y1="-1.8" x2="2" y2="0" width="0.2032" layer="51"/>
<pad name="1" x="-1" y="0" drill="0.7" diameter="1.4478" stop="no"/>
<pad name="2" x="1" y="0" drill="0.7" diameter="1.4478" stop="no"/>
<text x="-1.27" y="5.27" size="0.4064" layer="25">&gt;Name</text>
<text x="-1.27" y="4" size="0.4064" layer="27">&gt;Value</text>
<text x="0.6" y="0.7" size="1.27" layer="51">+</text>
<text x="-1.4" y="0.7" size="1.27" layer="51">-</text>
<polygon width="0.127" layer="30">
<vertex x="-0.9975" y="-0.6604" curve="-90.025935"/>
<vertex x="-1.6604" y="0" curve="-90.017354"/>
<vertex x="-1" y="0.6604" curve="-90"/>
<vertex x="-0.3396" y="0" curve="-90.078137"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="-1" y="-0.2865" curve="-90.08005"/>
<vertex x="-1.2865" y="0" curve="-90.040011"/>
<vertex x="-1" y="0.2865" curve="-90"/>
<vertex x="-0.7135" y="0" curve="-90"/>
</polygon>
<polygon width="0.127" layer="30">
<vertex x="1.0025" y="-0.6604" curve="-90.025935"/>
<vertex x="0.3396" y="0" curve="-90.017354"/>
<vertex x="1" y="0.6604" curve="-90"/>
<vertex x="1.6604" y="0" curve="-90.078137"/>
</polygon>
<polygon width="0.127" layer="29">
<vertex x="1" y="-0.2865" curve="-90.08005"/>
<vertex x="0.7135" y="0" curve="-90.040011"/>
<vertex x="1" y="0.2865" curve="-90"/>
<vertex x="1.2865" y="0" curve="-90"/>
</polygon>
</package>
<package name="SPRINGTERMINAL-2.54MM-2">
<wire x1="-4.2" y1="7.88" x2="-4.2" y2="-2.8" width="0.254" layer="21"/>
<wire x1="-4.2" y1="-2.8" x2="-4.2" y2="-4.72" width="0.254" layer="51"/>
<wire x1="-4.2" y1="-4.72" x2="3.44" y2="-4.72" width="0.254" layer="51"/>
<wire x1="3.44" y1="-4.72" x2="3.44" y2="-2.8" width="0.254" layer="51"/>
<wire x1="3.44" y1="7.88" x2="-4.2" y2="7.88" width="0.254" layer="21"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.254" layer="1"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.254" layer="16"/>
<wire x1="2.54" y1="0" x2="2.54" y2="5.08" width="0.254" layer="16"/>
<wire x1="2.54" y1="0" x2="2.54" y2="5.08" width="0.254" layer="1"/>
<wire x1="-4.2" y1="-2.8" x2="3.44" y2="-2.8" width="0.254" layer="21"/>
<wire x1="3.44" y1="4" x2="3.44" y2="1" width="0.254" layer="21"/>
<wire x1="3.44" y1="7.88" x2="3.44" y2="6" width="0.254" layer="21"/>
<wire x1="3.44" y1="-0.9" x2="3.44" y2="-2.8" width="0.254" layer="21"/>
<pad name="1" x="0" y="0" drill="1.1" diameter="1.9"/>
<pad name="P$2" x="0" y="5.08" drill="1.1" diameter="1.9"/>
<pad name="P$3" x="2.54" y="5.08" drill="1.1" diameter="1.9"/>
<pad name="2" x="2.54" y="0" drill="1.1" diameter="1.9"/>
</package>
<package name="1X02_2.54_SCREWTERM">
<pad name="P2" x="0" y="0" drill="1.016" shape="square"/>
<pad name="P1" x="2.54" y="0" drill="1.016" shape="square"/>
<wire x1="-1.5" y1="3.25" x2="4" y2="3.25" width="0.2032" layer="21"/>
<wire x1="4" y1="3.25" x2="4" y2="2.5" width="0.2032" layer="21"/>
<wire x1="4" y1="2.5" x2="4" y2="-3.25" width="0.2032" layer="21"/>
<wire x1="4" y1="-3.25" x2="-1.5" y2="-3.25" width="0.2032" layer="21"/>
<wire x1="-1.5" y1="-3.25" x2="-1.5" y2="2.5" width="0.2032" layer="21"/>
<wire x1="-1.5" y1="2.5" x2="-1.5" y2="3.25" width="0.2032" layer="21"/>
<wire x1="-1.5" y1="2.5" x2="4" y2="2.5" width="0.2032" layer="21"/>
</package>
<package name="JST-2-PTH-VERT">
<wire x1="-2.95" y1="-2.25" x2="-2.95" y2="2.25" width="0.2032" layer="21"/>
<wire x1="-2.95" y1="2.25" x2="2.95" y2="2.25" width="0.2032" layer="21"/>
<wire x1="2.95" y1="2.25" x2="2.95" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="2.95" y1="-2.25" x2="1" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-1" y1="-2.25" x2="-2.95" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-1" y1="-1.75" x2="1" y2="-1.75" width="0.2032" layer="21"/>
<wire x1="1" y1="-1.75" x2="1" y2="-2.25" width="0.2032" layer="21"/>
<wire x1="-1" y1="-1.75" x2="-1" y2="-2.25" width="0.2032" layer="21"/>
<pad name="1" x="-1" y="-0.55" drill="0.7" diameter="1.6"/>
<pad name="2" x="1" y="-0.55" drill="0.7" diameter="1.6"/>
<text x="-1.984" y="3" size="0.4064" layer="25">&gt;Name</text>
<text x="2.016" y="3" size="0.4064" layer="27">&gt;Value</text>
<text x="0.616" y="0.75" size="1.27" layer="51">+</text>
<text x="-1.384" y="0.75" size="1.27" layer="51">-</text>
</package>
<package name="1X01_LONGPAD">
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="0.635" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.1176" diameter="1.8796" shape="long" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="LUXEON-PAD">
<smd name="P$1" x="0" y="0" dx="3.9" dy="2.4" layer="1" roundness="25"/>
<text x="-1.5" y="2" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.5" y="-3" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="SMTRA-256-8-6">
<pad name="P$1" x="-1.9939" y="0" drill="1.3462"/>
<pad name="P$2" x="1.9939" y="0" drill="1.3462"/>
<smd name="P$3" x="0" y="0" dx="6.6548" dy="4.3434" layer="1" cream="no"/>
<text x="1.27" y="2.54" size="0.4064" layer="27">&gt;Value</text>
<text x="-2.54" y="2.54" size="0.4064" layer="25">&gt;Name</text>
<rectangle x1="-3.302" y1="0.762" x2="3.302" y2="2.032" layer="31"/>
<rectangle x1="-1.016" y1="0.508" x2="1.016" y2="0.762" layer="31"/>
<rectangle x1="-1.016" y1="-1.016" x2="1.016" y2="-0.762" layer="31"/>
<rectangle x1="-3.302" y1="-2.032" x2="3.302" y2="-0.762" layer="31"/>
<rectangle x1="-1.016" y1="-0.762" x2="1.016" y2="-0.508" layer="31"/>
<rectangle x1="2.794" y1="0.508" x2="3.302" y2="0.762" layer="31"/>
<rectangle x1="2.794" y1="-0.762" x2="3.302" y2="-0.508" layer="31"/>
<rectangle x1="-3.302" y1="-0.762" x2="-2.794" y2="-0.508" layer="31"/>
<rectangle x1="-3.302" y1="0.508" x2="-2.794" y2="0.762" layer="31"/>
</package>
<package name="1X01NS">
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
</package>
<package name="1X01">
<wire x1="1.27" y1="0.635" x2="0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="1.27" x2="-0.635" y2="1.27" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="-1.27" y2="0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="1.1938" y="1.8288" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="1X01_2MM">
<pad name="1" x="0" y="0" drill="2" diameter="3.302" rot="R90"/>
<text x="-1.3462" y="1.8288" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="1X01_OFFSET">
<wire x1="-1.27" y1="0.635" x2="-1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="-1.27" y1="-0.635" x2="-0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="0.635" y2="-1.27" width="0.2032" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="1.27" y2="-0.635" width="0.2032" layer="21"/>
<wire x1="1.27" y1="-0.635" x2="1.27" y2="0.635" width="0.2032" layer="21"/>
<pad name="1" x="0" y="0" drill="1.1176" diameter="1.8796" shape="offset" rot="R90"/>
<text x="1.1938" y="1.8288" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="PAD-1.5X4.5">
<smd name="P$1" x="0" y="0" dx="1.5" dy="2" layer="1"/>
</package>
<package name="1X01_POGOPIN_HOLE_LARGE">
<circle x="0" y="0" radius="0.635" width="0.127" layer="51"/>
<pad name="1" x="0" y="0" drill="0.9" diameter="0.8128" rot="R90" thermals="no"/>
<hole x="0" y="0" drill="1.5494"/>
</package>
<package name="1X01_POGOPIN_HOLE_0.58">
<circle x="0" y="0" radius="0.635" width="0.127" layer="51"/>
<pad name="1" x="0" y="0" drill="0.9" diameter="0.8128" rot="R90" thermals="no"/>
<hole x="0" y="0" drill="1.4732"/>
</package>
<package name="SNAP-FEMALE">
<pad name="1" x="0" y="0" drill="2.921" diameter="4.572"/>
<polygon width="0.254" layer="1">
<vertex x="-4.0005" y="0" curve="-89.997136"/>
<vertex x="0" y="4.0005" curve="-90.002865"/>
<vertex x="4.0005" y="0" curve="-89.997136"/>
<vertex x="0" y="-4.0005" curve="-89.997136"/>
</polygon>
<polygon width="0.3556" layer="29">
<vertex x="-4.0005" y="0" curve="-90.002865"/>
<vertex x="0" y="4.0005" curve="-90.002865"/>
<vertex x="4.0005" y="0" curve="-89.997136"/>
<vertex x="0" y="-4.0005" curve="-89.997136"/>
</polygon>
<polygon width="0.3556" layer="31">
<vertex x="-4.0005" y="0" curve="-89.997136"/>
<vertex x="0" y="4.0005" curve="-90.002865"/>
<vertex x="4.0005" y="0" curve="-89.997136"/>
<vertex x="0" y="-4.0005" curve="-89.997136"/>
</polygon>
<polygon width="0.3556" layer="41">
<vertex x="-4.0005" y="0" curve="-89.997136"/>
<vertex x="0" y="4.0005" curve="-90.002865"/>
<vertex x="4.0005" y="0" curve="-89.997136"/>
<vertex x="0" y="-4.0005" curve="-89.997136"/>
</polygon>
</package>
<package name="SNAP-MALE">
<smd name="2" x="0" y="0" dx="7.62" dy="7.62" layer="1" roundness="100"/>
</package>
<package name="SPRING-CONNECTOR">
<smd name="P$2" x="0" y="0" dx="7.112" dy="7.112" layer="1" roundness="100"/>
<text x="-1.3462" y="5.6388" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-1.27" y="-5.715" size="1.27" layer="27">&gt;VALUE</text>
</package>
<package name="1X01NS-KIT">
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90" stop="no"/>
<circle x="0" y="0" radius="0.508" width="0" layer="29"/>
<circle x="0" y="0" radius="0.9398" width="0" layer="30"/>
</package>
<package name="1X01_NO_SILK">
<pad name="1" x="0" y="0" drill="1.016" diameter="1.8796" rot="R90"/>
<text x="1.1938" y="1.8288" size="1.27" layer="25">&gt;NAME</text>
<text x="-1.27" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-0.254" y1="-0.254" x2="0.254" y2="0.254" layer="51"/>
</package>
<package name="SMTSO-256-ET-0.165DIA">
<circle x="0" y="0" radius="1.016" width="0.127" layer="51"/>
<wire x1="-1.016" y1="2.286" x2="-2.286" y2="1.016" width="1.016" layer="31" curve="42.075022"/>
<wire x1="2.286" y1="1.016" x2="1.016" y2="2.286" width="1.016" layer="31" curve="42.075022"/>
<wire x1="1.016" y1="-2.286" x2="2.286" y2="-1.016" width="1.016" layer="31" curve="42.075022"/>
<wire x1="-2.286" y1="-1.016" x2="-1.016" y2="-2.286" width="1.016" layer="31" curve="42.075022"/>
<pad name="P$1" x="0" y="0" drill="4.191" diameter="6.1976"/>
<text x="-2.54" y="1.27" size="0.8128" layer="49">.165 drill</text>
</package>
</packages>
<symbols>
<symbol name="M02">
<wire x1="3.81" y1="-2.54" x2="-2.54" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="1.27" y1="2.54" x2="2.54" y2="2.54" width="0.6096" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="-2.54" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-2.54" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-2.54" y1="5.08" x2="3.81" y2="5.08" width="0.4064" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="5.842" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="0" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
<pin name="2" x="7.62" y="2.54" visible="pad" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
<symbol name="M01">
<wire x1="3.81" y1="-2.54" x2="-2.54" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="1.27" y1="0" x2="2.54" y2="0" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="-2.54" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="3.81" y1="-2.54" x2="3.81" y2="2.54" width="0.4064" layer="94"/>
<wire x1="-2.54" y1="2.54" x2="3.81" y2="2.54" width="0.4064" layer="94"/>
<text x="-2.54" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<text x="-2.54" y="3.302" size="1.778" layer="95">&gt;NAME</text>
<pin name="1" x="7.62" y="0" visible="off" length="middle" direction="pas" swaplevel="1" rot="R180"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="M02" prefix="JP" uservalue="yes">
<description>Standard 2-pin 0.1" header. Use with &lt;br&gt;
- straight break away headers ( PRT-00116)&lt;br&gt;
- right angle break away headers (PRT-00553)&lt;br&gt;
- swiss pins (PRT-00743)&lt;br&gt;
- machine pins (PRT-00117)&lt;br&gt;
- female headers (PRT-00115)&lt;br&gt;&lt;br&gt;

 Molex polarized connector foot print use with: PRT-08233 with associated crimp pins and housings.&lt;br&gt;&lt;br&gt;

2.54_SCREWTERM for use with  PRT-10571.&lt;br&gt;&lt;br&gt;

3.5mm Screw Terminal footprints for  PRT-08084&lt;br&gt;&lt;br&gt;

5mm Screw Terminal footprints for use with PRT-08432</description>
<gates>
<gate name="G$1" symbol="M02" x="-2.54" y="0"/>
</gates>
<devices>
<device name="PTH" package="1X02">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="POLAR" package="MOLEX-1X2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3.5MM" package="SCREWTERMINAL-3.5MM-2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-08399" constant="no"/>
</technology>
</technologies>
</device>
<device name="-JST-2MM-SMT" package="JST-2-SMD">
<connects>
<connect gate="G$1" pin="1" pad="2"/>
<connect gate="G$1" pin="2" pad="1"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-11443"/>
</technology>
</technologies>
</device>
<device name="PTH2" package="1X02_BIG">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
<connect gate="G$1" pin="2" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="4UCON-15767" package="JST-2-SMD-VERT">
<connects>
<connect gate="G$1" pin="1" pad="GND"/>
<connect gate="G$1" pin="2" pad="VCC"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="ROCKER" package="R_SW_TH">
<connects>
<connect gate="G$1" pin="1" pad="P$3"/>
<connect gate="G$1" pin="2" pad="P$4"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="5MM" package="SCREWTERMINAL-5MM-2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="STOREFRONT_ID" value="PRT-08432" constant="no"/>
</technology>
</technologies>
</device>
<device name="LOCK" package="1X02_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="POLAR_LOCK" package="MOLEX-1X2_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="LOCK_LONGPADS" package="1X02_LOCK_LONGPADS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3.5MM_LOCK" package="SCREWTERMINAL-3.5MM-2_LOCK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-08399" constant="no"/>
</technology>
</technologies>
</device>
<device name="PTH3" package="1X02_LONGPADS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="1X02_NO_SILK" package="1X02_NO_SILK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="JST-PTH-2" package="JST-2-PTH">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-09863" constant="no"/>
<attribute name="SKU" value="PRT-09914" constant="no"/>
</technology>
</technologies>
</device>
<device name="PTH4" package="1X02_XTRA_BIG">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="POGO_PIN_HOLES_ONLY" package="1X02_PP_HOLES_ONLY">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3.5MM-NO_SILK" package="SCREWTERMINAL-3.5MM-2-NS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="PROD_ID" value="CONN-08399" constant="no"/>
</technology>
</technologies>
</device>
<device name="-JST-2-PTH-NO_SILK" package="JST-2-PTH-NS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="JST-PTH-2-KIT" package="JST-2-PTH-KIT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SPRING-2.54-RA" package="SPRINGTERMINAL-2.54MM-2">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="2.54MM_SCREWTERM" package="1X02_2.54_SCREWTERM">
<connects>
<connect gate="G$1" pin="1" pad="P1"/>
<connect gate="G$1" pin="2" pad="P2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="JST-PTH-VERT" package="JST-2-PTH-VERT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="M01" prefix="JP" uservalue="yes">
<description>&lt;b&gt;Header 1&lt;/b&gt;
Standard 1-pin 0.1" header. Use with straight break away headers (SKU : PRT-00116), right angle break away headers (PRT-00553), swiss pins (PRT-00743), machine pins (PRT-00117), and female headers (PRT-00115). SMTSO-256-ET is a "flush mount" nut for a 4-40 screw. The older package used to be too tight, and did not allow it to sit properly thru the drill hit. The latest (0.165DIA) fits nice and snug.</description>
<gates>
<gate name="G$1" symbol="M01" x="0" y="0"/>
</gates>
<devices>
<device name="PTH_LONGPAD" package="1X01_LONGPAD">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD" package="LUXEON-PAD">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMTRA-256-8-6" package="SMTRA-256-8-6">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMDNS" package="1X01NS">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH" package="1X01">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH_2MM" package="1X01_2MM">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="OFFSET" package="1X01_OFFSET">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMD-4.5X1.5" package="PAD-1.5X4.5">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="POGOPIN_HOLE_LARGE" package="1X01_POGOPIN_HOLE_LARGE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="POGOPIN_HOLE_0.58" package="1X01_POGOPIN_HOLE_0.58">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SNAP-FEMALE" package="SNAP-FEMALE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SNAP-MALE" package="SNAP-MALE">
<connects>
<connect gate="G$1" pin="1" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SPRING-CONN" package="SPRING-CONNECTOR">
<connects>
<connect gate="G$1" pin="1" pad="P$2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="NOSILK-KIT" package="1X01NS-KIT">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="PTH_NO_SILK_YES_STOP" package="1X01_NO_SILK">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="SMTSO-256-ET-0.165DIA" package="SMTSO-256-ET-0.165DIA">
<connects>
<connect gate="G$1" pin="1" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="TCXO" library="TT7" deviceset="I547-2P3_TCXO" device="" value="32MHz"/>
<part name="SUPPLY1" library="supply2" deviceset="GND" device=""/>
<part name="LCHOKE" library="TT7" deviceset="IND0402" device="" value="220nH / 390nH"/>
<part name="CD5" library="TT7" deviceset="CAP0402" device="" value="10nF"/>
<part name="R1" library="TT7" deviceset="RES0402" device="" value="91k"/>
<part name="CD1" library="TT7" deviceset="CAP0402" device="" value="15pF"/>
<part name="CD3" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="CD4" library="TT7" deviceset="CAP0402" device="" value="2.2uF"/>
<part name="SUPPLY2" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY3" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY4" library="supply2" deviceset="GND" device=""/>
<part name="L0" library="TT7" deviceset="IND0402" device="" value="33nH / 47nH"/>
<part name="C0" library="TT7" deviceset="CAP0402" device="" value="9.1pF / 470pF"/>
<part name="CM" library="TT7" deviceset="CAP0402" device="" value="15pF / 18pF"/>
<part name="CM1" library="TT7" deviceset="CAP0402" device="" value="12pF / 18pF"/>
<part name="CM2" library="TT7" deviceset="CAP0402" device="" value="10pF / NO-OP"/>
<part name="LM1" library="TT7" deviceset="IND0402" device="" value="30nH / 68nH"/>
<part name="LM2" library="TT7" deviceset="IND0402" device="" value="36nH / 47nH"/>
<part name="SUPPLY6" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY7" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY8" library="supply2" deviceset="GND" device=""/>
<part name="RF-2" library="TT7" deviceset="HOLE-1.87" device=""/>
<part name="RF-1" library="TT7" deviceset="HOLE-1.87" device=""/>
<part name="SUPPLY9" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY11" library="supply2" deviceset="GND" device=""/>
<part name="U1" library="TT7" deviceset="LTC3105" device=""/>
<part name="LTC-10UH" library="TT7" deviceset="DLJ4018" device=""/>
<part name="COUT" library="TT7" deviceset="CAP0805" device="" value="10uF"/>
<part name="R3" library="TT7" deviceset="RES0402" device="" value="1.5M"/>
<part name="R4" library="TT7" deviceset="RES0402" device="" value="470k"/>
<part name="SUPPLY12" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY13" library="supply2" deviceset="GND" device=""/>
<part name="R5" library="TT7" deviceset="RES0402" device="" value="91k"/>
<part name="AUX" library="TT7" deviceset="CAP0603" device="" value="1uF"/>
<part name="LDO" library="TT7" deviceset="CAP0603" device="" value="4.7uF"/>
<part name="SUPPLY15" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY16" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY17" library="supply2" deviceset="GND" device=""/>
<part name="C1" library="TT7" deviceset="CAP0603" device="" value="4.7uF"/>
<part name="C2" library="TT7" deviceset="CAP0805" device="" value="10uF"/>
<part name="L1" library="TT7" deviceset="DLJ3015" device="" value="3.3uH"/>
<part name="SUPPLY19" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY20" library="supply2" deviceset="GND" device=""/>
<part name="U$2" library="TT7" deviceset="UBLOX_MAX-7C" device=""/>
<part name="SUPPLY21" library="supply2" deviceset="GND" device=""/>
<part name="C3" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="RF_IN+" library="TT7" deviceset="PAD-2.5X1.5" device=""/>
<part name="SUPPLY22" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY23" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY24" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY25" library="supply2" deviceset="GND" device=""/>
<part name="C4" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="C5" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="C6" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="C7" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="SUPPLY26" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY27" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY28" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY29" library="supply2" deviceset="GND" device=""/>
<part name="C8" library="TT7" deviceset="CAP0805" device="" value="10uF"/>
<part name="SUPPLY30" library="supply2" deviceset="GND" device=""/>
<part name="C9" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="R6" library="TT7" deviceset="RES0402" device="" value="10k"/>
<part name="SUPPLY31" library="supply2" deviceset="GND" device=""/>
<part name="R7" library="TT7" deviceset="RES0402" device="" value="4.7k"/>
<part name="R8" library="TT7" deviceset="RES0402" device="" value="4.7k"/>
<part name="R9" library="TT7" deviceset="RES0402" device="" value="0R"/>
<part name="SUPPLY32" library="supply2" deviceset="GND" device=""/>
<part name="R12" library="TT7" deviceset="RES0402" device="" value="100R"/>
<part name="R13" library="TT7" deviceset="RES0402" device="" value="100R"/>
<part name="U$3" library="TT7" deviceset="LED0603" device=""/>
<part name="U$4" library="TT7" deviceset="LED0603" device=""/>
<part name="SUPPLY33" library="supply2" deviceset="GND" device=""/>
<part name="R14" library="TT7" deviceset="RES0603" device="" value="1M"/>
<part name="R15" library="TT7" deviceset="RES0603" device="" value="1M"/>
<part name="U4" library="TT7" deviceset="SAM3S8B-AU" device=""/>
<part name="CFPX-104" library="TT7" deviceset="CFPX-104" device="" value="16MHz"/>
<part name="C10" library="TT7" deviceset="CAP0402" device="" value="15pF"/>
<part name="SUPPLY35" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY36" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY34" library="supply2" deviceset="GND" device=""/>
<part name="C12" library="TT7" deviceset="CAP0402" device="" value="15pF"/>
<part name="C11" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="C13" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="C14" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="SUPPLY37" library="supply2" deviceset="GND" device=""/>
<part name="C15" library="TT7" deviceset="CAP0603" device="" value="10uF"/>
<part name="SUPPLY38" library="supply2" deviceset="GND" device=""/>
<part name="C16" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="SUPPLY39" library="supply2" deviceset="GND" device=""/>
<part name="C17" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="C18" library="TT7" deviceset="CAP0402" device="" value="2.2uF"/>
<part name="SUPPLY40" library="supply2" deviceset="GND" device=""/>
<part name="C19" library="TT7" deviceset="CAP0402" device="" value="2.2uF"/>
<part name="C20" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="C21" library="TT7" deviceset="CAP0402" device="" value="2.2uF"/>
<part name="C22" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="C23" library="TT7" deviceset="CAP0402" device="" value="2.2uF"/>
<part name="C24" library="TT7" deviceset="CAP0402" device="" value="100nF"/>
<part name="SUPPLY41" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY42" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY43" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY44" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY45" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY46" library="supply2" deviceset="GND" device=""/>
<part name="U$10" library="TT7" deviceset="USB_MICRO_B" device=""/>
<part name="SUPPLY47" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY48" library="supply2" deviceset="GND" device=""/>
<part name="U$9" library="TT7" deviceset="MCP1700" device=""/>
<part name="C25" library="TT7" deviceset="CAP0603" device="" value="1uF"/>
<part name="C26" library="TT7" deviceset="CAP0603" device="" value="1uF"/>
<part name="R10" library="TT7" deviceset="RES0402" device="" value="27R"/>
<part name="R11" library="TT7" deviceset="RES0402" device="" value="27R"/>
<part name="SUPPLY49" library="supply2" deviceset="GND" device=""/>
<part name="JP3" library="SparkFun-Connectors" deviceset="M02" device="1X02_NO_SILK"/>
<part name="JP4" library="SparkFun-Connectors" deviceset="M02" device="1X02_NO_SILK"/>
<part name="JP5" library="SparkFun-Connectors" deviceset="M02" device="1X02_NO_SILK"/>
<part name="JP6" library="SparkFun-Connectors" deviceset="M02" device="1X02_NO_SILK"/>
<part name="JP2" library="SparkFun-Connectors" deviceset="M02" device="1X02_NO_SILK"/>
<part name="JP7" library="SparkFun-Connectors" deviceset="M01" device="PTH_NO_SILK_YES_STOP"/>
<part name="LH" library="TT7" deviceset="IND0402" device="" value="NO-OP / 82nH"/>
<part name="CH" library="TT7" deviceset="CAP0402" device="" value="NO-OP / 11pF"/>
<part name="RH" library="TT7" deviceset="RES0402" device="" value="NO-OP / 50R"/>
<part name="SUPPLY52" library="supply2" deviceset="GND" device=""/>
<part name="RF+" library="TT7" deviceset="PAD-3X1.5" device=""/>
<part name="LM3" library="TT7" deviceset="IND0402" device="" value="22nH / NO-OP"/>
<part name="U$15" library="TT7" deviceset="MT9D111-AVX145602-NEW" device=""/>
<part name="CIN" library="TT7" deviceset="CAP0603" device="" value="10uF"/>
<part name="U$1" library="TT7" deviceset="SI4060_VIAS" device=""/>
<part name="SUPPLY5" library="supply2" deviceset="GND" device=""/>
<part name="U3" library="TT7" deviceset="TPS63031_VIAS" device=""/>
<part name="ME6211-2.8V" library="TT7" deviceset="ME6211_NEW" device=""/>
<part name="ME6211-1.8V" library="TT7" deviceset="ME6211_NEW" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<wire x1="0" y1="0" x2="205.74" y2="0" width="0.1524" layer="94"/>
<wire x1="205.74" y1="0" x2="205.74" y2="127" width="0.1524" layer="94"/>
<wire x1="205.74" y1="127" x2="0" y2="127" width="0.1524" layer="94"/>
<wire x1="0" y1="127" x2="0" y2="0" width="0.1524" layer="94"/>
<text x="7.62" y="119.38" size="2.54" layer="94">Si4463</text>
<text x="7.62" y="114.3" size="1.778" layer="94">434MHz - 20dBm CLE Split TX/RX</text>
<wire x1="213.36" y1="127" x2="421.64" y2="127" width="0.1524" layer="94"/>
<wire x1="421.64" y1="127" x2="421.64" y2="0" width="0.1524" layer="94"/>
<wire x1="421.64" y1="0" x2="213.36" y2="0" width="0.1524" layer="94"/>
<wire x1="213.36" y1="0" x2="213.36" y2="127" width="0.1524" layer="94"/>
<text x="220.98" y="119.38" size="2.54" layer="94">LTC3105</text>
<text x="345.44" y="119.38" size="2.54" layer="94">TPS63031</text>
<text x="220.98" y="114.3" size="1.778" layer="94">FB resistors - 1.5M and 470k for 4.208V Vout</text>
<text x="220.98" y="109.22" size="1.778" layer="94">MPPC resistor - 91k performed better than 180k</text>
<text x="220.98" y="104.14" size="1.778" layer="94">4x Solar Cell (5x2.5) - 2.4V 430mA max</text>
<text x="345.44" y="114.3" size="1.778" layer="94">Input Voltage 1.8V - 5.5V, Output Voltage 3.3V</text>
<text x="345.44" y="109.22" size="1.778" layer="94">Step Down Mode 800mA max, Boost Mode 500mA max</text>
<wire x1="421.64" y1="134.62" x2="294.64" y2="134.62" width="0.1524" layer="94"/>
<wire x1="294.64" y1="134.62" x2="294.64" y2="226.06" width="0.1524" layer="94"/>
<wire x1="294.64" y1="226.06" x2="421.64" y2="226.06" width="0.1524" layer="94"/>
<wire x1="421.64" y1="226.06" x2="421.64" y2="134.62" width="0.1524" layer="94"/>
<text x="302.26" y="218.44" size="2.54" layer="94">U-BLOX MAX-7C</text>
<text x="302.26" y="213.36" size="1.778" layer="94">Power Supply 1.65V - 3.6V</text>
<text x="302.26" y="208.28" size="1.778" layer="94">Cold Start - 30s, Warm Start - 28s, Hot Start - 1s</text>
<text x="302.26" y="203.2" size="1.778" layer="94">Limits: 4g, 500m/s, 50000m</text>
<wire x1="287.02" y1="134.62" x2="99.06" y2="134.62" width="0.1524" layer="94"/>
<wire x1="99.06" y1="134.62" x2="99.06" y2="226.06" width="0.1524" layer="94"/>
<wire x1="99.06" y1="226.06" x2="287.02" y2="226.06" width="0.1524" layer="94"/>
<wire x1="287.02" y1="226.06" x2="287.02" y2="134.62" width="0.1524" layer="94"/>
<text x="106.68" y="218.44" size="2.54" layer="94">MT9D111</text>
<wire x1="91.44" y1="134.62" x2="0" y2="134.62" width="0.1524" layer="94"/>
<wire x1="0" y1="134.62" x2="0" y2="226.06" width="0.1524" layer="94"/>
<wire x1="0" y1="226.06" x2="91.44" y2="226.06" width="0.1524" layer="94"/>
<wire x1="91.44" y1="226.06" x2="91.44" y2="134.62" width="0.1524" layer="94"/>
<wire x1="0" y1="233.68" x2="421.64" y2="233.68" width="0.1524" layer="94"/>
<wire x1="421.64" y1="233.68" x2="421.64" y2="411.48" width="0.1524" layer="94"/>
<wire x1="421.64" y1="411.48" x2="0" y2="411.48" width="0.1524" layer="94"/>
<wire x1="0" y1="411.48" x2="0" y2="233.68" width="0.1524" layer="94"/>
<text x="7.62" y="403.86" size="2.54" layer="94">SAM3S8B-AU</text>
<text x="106.68" y="213.36" size="1.778" layer="94">CLK - input clock &gt;6MHz (PWM)</text>
<text x="106.68" y="208.28" size="1.778" layer="94">Parallel Capture Mode, PDC (SAM3S8)</text>
<text x="7.62" y="218.44" size="2.54" layer="94">LEDs</text>
<text x="7.62" y="180.34" size="2.54" layer="94">ANALOG READ</text>
<text x="7.62" y="398.78" size="1.778" layer="94">External crystal 16MHz, Internal 32kHz RC oscillator</text>
<text x="7.62" y="175.26" size="1.778" layer="94">Solar Panels' voltage</text>
<text x="7.62" y="170.18" size="1.778" layer="94">Battery voltage</text>
<text x="55.88" y="345.44" size="1.778" layer="97">VDDIO</text>
<text x="99.06" y="345.44" size="1.778" layer="97">VDDCORE</text>
<text x="93.98" y="299.72" size="1.778" layer="97">VDDIN</text>
<text x="93.98" y="279.4" size="1.778" layer="97">VDDPLL</text>
<text x="55.88" y="261.62" size="1.778" layer="97">VDDOUT</text>
<text x="7.62" y="393.7" size="1.778" layer="94">PA8 can provide enough current at 3.3V for the TCXO (1.5mA max) - enable/disable</text>
<text x="7.62" y="388.62" size="1.778" layer="94">PA1 serves as a USB plug-in detection</text>
<text x="7.62" y="383.54" size="1.778" layer="94">Possibility of supplying the board through VBUS pin - 3.65V min 6V max</text>
<text x="7.62" y="378.46" size="1.778" layer="94">Due to MT9D111, I2C lines are pulled up to 2.8V (not 3.3V).</text>
<wire x1="429.26" y1="411.48" x2="510.54" y2="411.48" width="0.1524" layer="94"/>
<wire x1="510.54" y1="411.48" x2="510.54" y2="337.82" width="0.1524" layer="94"/>
<wire x1="510.54" y1="337.82" x2="429.26" y2="337.82" width="0.1524" layer="94"/>
<wire x1="429.26" y1="337.82" x2="429.26" y2="411.48" width="0.1524" layer="94"/>
<text x="436.88" y="398.78" size="1.778" layer="94">ADVREF connected to 3.3V.</text>
<text x="436.88" y="403.86" size="2.54" layer="94">REVISION from v1.4 (OSHpark compatible)</text>
<text x="436.88" y="393.7" size="1.778" layer="94">MT9D111 footprint narrowed.</text>
<text x="436.88" y="388.62" size="1.778" layer="94">Vias inside MT9D111 connector re-wired.</text>
<text x="436.88" y="383.54" size="1.778" layer="94">Si4463 matching re-done.</text>
<text x="436.88" y="378.46" size="1.778" layer="94">Added and moved antenna pads. Possibility of SMA connector.</text>
<text x="436.88" y="373.38" size="1.778" layer="94">Better pads for SOLAR and BATTERY.</text>
<text x="436.88" y="368.3" size="1.778" layer="94">Possibility for a powerup jumper.</text>
<text x="7.62" y="109.22" size="1.778" layer="94">169MHz - 20dBm SQW Split TX/RX</text>
<text x="436.88" y="363.22" size="1.778" layer="94">Added supercap pads.</text>
<text x="436.88" y="358.14" size="1.778" layer="94">Si4060 and TPS63031 footprint with vias</text>
<text x="436.88" y="353.06" size="1.778" layer="94">Added holes to hang the tracker.</text>
<text x="436.88" y="347.98" size="1.778" layer="94">Removed VBUS powered info line (PA1).</text>
<text x="436.88" y="342.9" size="1.778" layer="94">Added TIMEPULSE connection to Ublox.</text>
</plain>
<instances>
<instance part="TCXO" gate="G$1" x="147.32" y="109.22" smashed="yes"/>
<instance part="SUPPLY1" gate="GND" x="139.7" y="45.72"/>
<instance part="LCHOKE" gate="G$1" x="129.54" y="38.1" rot="R90"/>
<instance part="CD5" gate="G$1" x="121.92" y="104.14" rot="R90"/>
<instance part="R1" gate="G$1" x="119.38" y="81.28" rot="R180"/>
<instance part="CD1" gate="G$1" x="144.78" y="22.86" rot="R90"/>
<instance part="CD3" gate="G$1" x="170.18" y="22.86" rot="R90"/>
<instance part="CD4" gate="G$1" x="182.88" y="22.86" rot="R90"/>
<instance part="SUPPLY2" gate="GND" x="144.78" y="10.16"/>
<instance part="SUPPLY3" gate="GND" x="137.16" y="76.2"/>
<instance part="SUPPLY4" gate="GND" x="121.92" y="93.98"/>
<instance part="L0" gate="G$1" x="99.06" y="53.34"/>
<instance part="C0" gate="G$1" x="121.92" y="53.34"/>
<instance part="CM" gate="G$1" x="86.36" y="40.64" rot="R90"/>
<instance part="CM1" gate="G$1" x="66.04" y="40.64" rot="R90"/>
<instance part="CM2" gate="G$1" x="45.72" y="40.64" rot="R90"/>
<instance part="LM1" gate="G$1" x="76.2" y="53.34"/>
<instance part="LM2" gate="G$1" x="55.88" y="53.34"/>
<instance part="SUPPLY6" gate="GND" x="86.36" y="30.48"/>
<instance part="SUPPLY7" gate="GND" x="66.04" y="30.48"/>
<instance part="SUPPLY8" gate="GND" x="45.72" y="30.48"/>
<instance part="RF-2" gate="G$1" x="71.12" y="88.9" smashed="yes" rot="R180">
<attribute name="VALUE" x="66.04" y="86.36" size="1.27" layer="96" rot="R90"/>
<attribute name="NAME" x="76.2" y="88.9" size="1.27" layer="95" rot="R270"/>
</instance>
<instance part="RF-1" gate="G$1" x="55.88" y="88.9" smashed="yes" rot="R180">
<attribute name="VALUE" x="50.8" y="86.36" size="1.27" layer="96" rot="R90"/>
<attribute name="NAME" x="60.96" y="88.9" size="1.27" layer="95" rot="R270"/>
</instance>
<instance part="SUPPLY9" gate="GND" x="55.88" y="76.2"/>
<instance part="SUPPLY11" gate="GND" x="109.22" y="76.2"/>
<instance part="U1" gate="G$1" x="269.24" y="55.88" smashed="yes">
<attribute name="VALUE" x="266.86" y="50.42" size="1.27" layer="96"/>
</instance>
<instance part="LTC-10UH" gate="G$1" x="297.18" y="45.72" rot="R270"/>
<instance part="COUT" gate="G$1" x="299.72" y="66.04"/>
<instance part="R3" gate="G$1" x="274.32" y="88.9"/>
<instance part="R4" gate="G$1" x="246.38" y="88.9"/>
<instance part="SUPPLY12" gate="GND" x="251.46" y="25.4"/>
<instance part="SUPPLY13" gate="GND" x="269.24" y="30.48"/>
<instance part="R5" gate="G$1" x="241.3" y="40.64" rot="R90"/>
<instance part="AUX" gate="G$1" x="274.32" y="73.66"/>
<instance part="LDO" gate="G$1" x="241.3" y="58.42"/>
<instance part="SUPPLY15" gate="GND" x="264.16" y="68.58"/>
<instance part="SUPPLY16" gate="GND" x="307.34" y="60.96"/>
<instance part="SUPPLY17" gate="GND" x="236.22" y="83.82"/>
<instance part="C1" gate="G$1" x="370.84" y="33.02" rot="R180"/>
<instance part="C2" gate="G$1" x="370.84" y="78.74" rot="R180"/>
<instance part="L1" gate="G$1" x="350.52" y="53.34" rot="R90"/>
<instance part="SUPPLY19" gate="GND" x="381" y="27.94"/>
<instance part="SUPPLY20" gate="GND" x="381" y="73.66"/>
<instance part="U$2" gate="G$1" x="360.68" y="177.8"/>
<instance part="SUPPLY21" gate="GND" x="327.66" y="170.18"/>
<instance part="C3" gate="G$1" x="403.86" y="175.26" rot="R90"/>
<instance part="RF_IN+" gate="G$1" x="312.42" y="187.96" rot="R180"/>
<instance part="SUPPLY22" gate="GND" x="403.86" y="165.1"/>
<instance part="SUPPLY23" gate="GND" x="386.08" y="147.32"/>
<instance part="SUPPLY24" gate="GND" x="251.46" y="147.32"/>
<instance part="SUPPLY25" gate="GND" x="215.9" y="147.32"/>
<instance part="C4" gate="G$1" x="139.7" y="193.04" rot="R90"/>
<instance part="C5" gate="G$1" x="182.88" y="193.04" rot="R90"/>
<instance part="C6" gate="G$1" x="182.88" y="160.02" rot="R90"/>
<instance part="C7" gate="G$1" x="139.7" y="160.02" rot="R90"/>
<instance part="SUPPLY26" gate="GND" x="182.88" y="147.32"/>
<instance part="SUPPLY27" gate="GND" x="139.7" y="147.32"/>
<instance part="SUPPLY28" gate="GND" x="139.7" y="180.34"/>
<instance part="SUPPLY29" gate="GND" x="182.88" y="180.34"/>
<instance part="C8" gate="G$1" x="114.3" y="177.8" rot="R90"/>
<instance part="SUPPLY30" gate="GND" x="114.3" y="165.1"/>
<instance part="C9" gate="G$1" x="233.68" y="215.9" rot="R180"/>
<instance part="R6" gate="G$1" x="215.9" y="208.28"/>
<instance part="SUPPLY31" gate="GND" x="248.92" y="210.82"/>
<instance part="R7" gate="G$1" x="264.16" y="213.36"/>
<instance part="R8" gate="G$1" x="264.16" y="190.5"/>
<instance part="R9" gate="G$1" x="58.42" y="172.72"/>
<instance part="SUPPLY32" gate="GND" x="73.66" y="147.32"/>
<instance part="R12" gate="G$1" x="63.5" y="210.82"/>
<instance part="R13" gate="G$1" x="63.5" y="195.58"/>
<instance part="U$3" gate="G$1" x="45.72" y="210.82"/>
<instance part="U$4" gate="G$1" x="45.72" y="195.58"/>
<instance part="SUPPLY33" gate="GND" x="73.66" y="190.5"/>
<instance part="R14" gate="G$1" x="40.64" y="152.4"/>
<instance part="R15" gate="G$1" x="60.96" y="152.4"/>
<instance part="U4" gate="G$1" x="203.2" y="309.88" smashed="yes">
<attribute name="VALUE" x="198.12" y="312.42" size="1.778" layer="96"/>
</instance>
<instance part="CFPX-104" gate="G$1" x="297.18" y="279.4"/>
<instance part="C10" gate="G$1" x="309.88" y="266.7" rot="R90"/>
<instance part="SUPPLY35" gate="GND" x="317.5" y="271.78"/>
<instance part="SUPPLY36" gate="GND" x="276.86" y="276.86"/>
<instance part="SUPPLY34" gate="GND" x="297.18" y="254"/>
<instance part="C12" gate="G$1" x="284.48" y="266.7" rot="R90"/>
<instance part="C11" gate="G$1" x="83.82" y="350.52"/>
<instance part="C13" gate="G$1" x="83.82" y="337.82"/>
<instance part="C14" gate="G$1" x="83.82" y="325.12"/>
<instance part="SUPPLY37" gate="GND" x="73.66" y="320.04"/>
<instance part="C15" gate="G$1" x="83.82" y="304.8"/>
<instance part="SUPPLY38" gate="GND" x="73.66" y="299.72"/>
<instance part="C16" gate="G$1" x="83.82" y="284.48"/>
<instance part="SUPPLY39" gate="GND" x="73.66" y="279.4"/>
<instance part="C17" gate="G$1" x="40.64" y="254"/>
<instance part="C18" gate="G$1" x="40.64" y="266.7"/>
<instance part="SUPPLY40" gate="GND" x="30.48" y="248.92"/>
<instance part="C19" gate="G$1" x="40.64" y="325.12"/>
<instance part="C20" gate="G$1" x="40.64" y="312.42"/>
<instance part="C21" gate="G$1" x="40.64" y="299.72"/>
<instance part="C22" gate="G$1" x="40.64" y="287.02"/>
<instance part="C23" gate="G$1" x="40.64" y="350.52"/>
<instance part="C24" gate="G$1" x="40.64" y="337.82"/>
<instance part="SUPPLY41" gate="GND" x="30.48" y="281.94"/>
<instance part="SUPPLY42" gate="GND" x="177.8" y="271.78"/>
<instance part="SUPPLY43" gate="GND" x="152.4" y="320.04"/>
<instance part="SUPPLY44" gate="GND" x="254" y="317.5"/>
<instance part="SUPPLY45" gate="GND" x="190.5" y="353.06"/>
<instance part="SUPPLY46" gate="GND" x="226.06" y="353.06"/>
<instance part="U$10" gate="G$1" x="386.08" y="330.2"/>
<instance part="SUPPLY47" gate="GND" x="401.32" y="320.04"/>
<instance part="SUPPLY48" gate="GND" x="370.84" y="320.04"/>
<instance part="U$9" gate="G$1" x="345.44" y="370.84"/>
<instance part="C25" gate="G$1" x="332.74" y="360.68" rot="R90"/>
<instance part="C26" gate="G$1" x="358.14" y="360.68" rot="R90"/>
<instance part="R10" gate="G$1" x="350.52" y="335.28"/>
<instance part="R11" gate="G$1" x="350.52" y="322.58"/>
<instance part="SUPPLY49" gate="GND" x="332.74" y="350.52"/>
<instance part="JP3" gate="G$1" x="363.22" y="271.78" rot="R180"/>
<instance part="JP4" gate="G$1" x="363.22" y="287.02" rot="R180"/>
<instance part="JP5" gate="G$1" x="363.22" y="256.54" rot="R180"/>
<instance part="JP6" gate="G$1" x="401.32" y="287.02" rot="R180"/>
<instance part="JP2" gate="G$1" x="401.32" y="256.54" rot="R180"/>
<instance part="JP7" gate="G$1" x="401.32" y="269.24" rot="R180"/>
<instance part="LH" gate="G$1" x="104.14" y="35.56" rot="R90"/>
<instance part="CH" gate="G$1" x="114.3" y="35.56" rot="R90"/>
<instance part="RH" gate="G$1" x="96.52" y="15.24"/>
<instance part="SUPPLY52" gate="GND" x="86.36" y="10.16"/>
<instance part="RF+" gate="G$1" x="17.78" y="53.34" rot="R180"/>
<instance part="LM3" gate="G$1" x="35.56" y="53.34"/>
<instance part="U$15" gate="G$1" x="233.68" y="170.18" smashed="yes"/>
<instance part="CIN" gate="G$1" x="279.4" y="35.56"/>
<instance part="U$1" gate="G$1" x="165.1" y="60.96" smashed="yes">
<attribute name="VALUE" x="157.48" y="63.5" size="1.778" layer="96"/>
</instance>
<instance part="SUPPLY5" gate="GND" x="195.58" y="43.18"/>
<instance part="U3" gate="G$1" x="378.46" y="53.34" smashed="yes">
<attribute name="VALUE" x="372.84" y="62.34" size="1.27" layer="96"/>
</instance>
<instance part="ME6211-2.8V" gate="G$1" x="162.56" y="162.56" smashed="yes">
<attribute name="NAME" x="154.94" y="172.72" size="1.778" layer="95"/>
</instance>
<instance part="ME6211-1.8V" gate="G$1" x="162.56" y="195.58" smashed="yes">
<attribute name="NAME" x="154.94" y="205.74" size="1.778" layer="95"/>
</instance>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="SUPPLY2" gate="GND" pin="GND"/>
<pinref part="CD1" gate="G$1" pin="P$1"/>
<wire x1="144.78" y1="12.7" x2="144.78" y2="15.24" width="0.1524" layer="91"/>
<wire x1="144.78" y1="15.24" x2="144.78" y2="17.78" width="0.1524" layer="91"/>
<junction x="144.78" y="15.24"/>
<pinref part="CD4" gate="G$1" pin="P$1"/>
<wire x1="144.78" y1="15.24" x2="170.18" y2="15.24" width="0.1524" layer="91"/>
<wire x1="170.18" y1="15.24" x2="182.88" y2="15.24" width="0.1524" layer="91"/>
<wire x1="182.88" y1="15.24" x2="182.88" y2="17.78" width="0.1524" layer="91"/>
<pinref part="CD3" gate="G$1" pin="P$1"/>
<wire x1="170.18" y1="17.78" x2="170.18" y2="15.24" width="0.1524" layer="91"/>
<junction x="170.18" y="15.24"/>
</segment>
<segment>
<pinref part="SUPPLY1" gate="GND" pin="GND"/>
<wire x1="139.7" y1="48.26" x2="139.7" y2="50.8" width="0.1524" layer="91"/>
<wire x1="139.7" y1="50.8" x2="142.24" y2="50.8" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="NC3"/>
</segment>
<segment>
<pinref part="SUPPLY3" gate="GND" pin="GND"/>
<wire x1="142.24" y1="78.74" x2="137.16" y2="78.74" width="0.1524" layer="91"/>
<wire x1="165.1" y1="83.82" x2="165.1" y2="88.9" width="0.1524" layer="91"/>
<wire x1="165.1" y1="88.9" x2="137.16" y2="88.9" width="0.1524" layer="91"/>
<wire x1="137.16" y1="88.9" x2="137.16" y2="78.74" width="0.1524" layer="91"/>
<junction x="137.16" y="78.74"/>
<wire x1="165.1" y1="88.9" x2="165.1" y2="106.68" width="0.1524" layer="91"/>
<junction x="165.1" y="88.9"/>
<pinref part="TCXO" gate="G$1" pin="GND"/>
<wire x1="165.1" y1="106.68" x2="162.56" y2="106.68" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="GND"/>
<pinref part="U$1" gate="G$1" pin="GNDP"/>
</segment>
<segment>
<pinref part="SUPPLY4" gate="GND" pin="GND"/>
<pinref part="CD5" gate="G$1" pin="P$1"/>
<wire x1="121.92" y1="96.52" x2="121.92" y2="99.06" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY8" gate="GND" pin="GND"/>
<pinref part="CM2" gate="G$1" pin="P$1"/>
<wire x1="45.72" y1="33.02" x2="45.72" y2="35.56" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY7" gate="GND" pin="GND"/>
<pinref part="CM1" gate="G$1" pin="P$1"/>
<wire x1="66.04" y1="33.02" x2="66.04" y2="35.56" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY6" gate="GND" pin="GND"/>
<pinref part="CM" gate="G$1" pin="P$1"/>
<wire x1="86.36" y1="33.02" x2="86.36" y2="35.56" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R1" gate="G$1" pin="P$2"/>
<wire x1="111.76" y1="81.28" x2="109.22" y2="81.28" width="0.1524" layer="91"/>
<wire x1="109.22" y1="81.28" x2="109.22" y2="78.74" width="0.1524" layer="91"/>
<pinref part="SUPPLY11" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="GND@6"/>
<wire x1="254" y1="48.26" x2="251.46" y2="48.26" width="0.1524" layer="91"/>
<pinref part="SUPPLY12" gate="GND" pin="GND"/>
<wire x1="251.46" y1="48.26" x2="251.46" y2="43.18" width="0.1524" layer="91"/>
<pinref part="U1" gate="G$1" pin="GND@7"/>
<wire x1="251.46" y1="43.18" x2="251.46" y2="30.48" width="0.1524" layer="91"/>
<wire x1="251.46" y1="30.48" x2="251.46" y2="27.94" width="0.1524" layer="91"/>
<wire x1="284.48" y1="48.26" x2="284.48" y2="43.18" width="0.1524" layer="91"/>
<wire x1="284.48" y1="43.18" x2="251.46" y2="43.18" width="0.1524" layer="91"/>
<junction x="251.46" y="43.18"/>
<pinref part="R5" gate="G$1" pin="P$1"/>
<wire x1="241.3" y1="33.02" x2="241.3" y2="30.48" width="0.1524" layer="91"/>
<wire x1="241.3" y1="30.48" x2="251.46" y2="30.48" width="0.1524" layer="91"/>
<junction x="251.46" y="30.48"/>
<pinref part="U1" gate="G$1" pin="FBLDO"/>
<wire x1="254" y1="55.88" x2="251.46" y2="55.88" width="0.1524" layer="91"/>
<wire x1="251.46" y1="55.88" x2="251.46" y2="48.26" width="0.1524" layer="91"/>
<junction x="251.46" y="48.26"/>
<pinref part="LDO" gate="G$1" pin="P$1"/>
<wire x1="236.22" y1="58.42" x2="231.14" y2="58.42" width="0.1524" layer="91"/>
<wire x1="231.14" y1="58.42" x2="231.14" y2="30.48" width="0.1524" layer="91"/>
<wire x1="231.14" y1="30.48" x2="241.3" y2="30.48" width="0.1524" layer="91"/>
<junction x="241.3" y="30.48"/>
</segment>
<segment>
<pinref part="SUPPLY13" gate="GND" pin="GND"/>
<wire x1="269.24" y1="33.02" x2="269.24" y2="35.56" width="0.1524" layer="91"/>
<wire x1="269.24" y1="35.56" x2="274.32" y2="35.56" width="0.1524" layer="91"/>
<pinref part="CIN" gate="G$1" pin="P$1"/>
</segment>
<segment>
<pinref part="AUX" gate="G$1" pin="P$1"/>
<pinref part="SUPPLY15" gate="GND" pin="GND"/>
<wire x1="269.24" y1="73.66" x2="264.16" y2="73.66" width="0.1524" layer="91"/>
<wire x1="264.16" y1="73.66" x2="264.16" y2="71.12" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY16" gate="GND" pin="GND"/>
<wire x1="307.34" y1="63.5" x2="307.34" y2="66.04" width="0.1524" layer="91"/>
<pinref part="COUT" gate="G$1" pin="P$2"/>
<wire x1="307.34" y1="66.04" x2="304.8" y2="66.04" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="R4" gate="G$1" pin="P$1"/>
<wire x1="238.76" y1="88.9" x2="236.22" y2="88.9" width="0.1524" layer="91"/>
<wire x1="236.22" y1="88.9" x2="236.22" y2="86.36" width="0.1524" layer="91"/>
<pinref part="SUPPLY17" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="C1" gate="G$1" pin="P$1"/>
<pinref part="SUPPLY19" gate="GND" pin="GND"/>
<wire x1="375.92" y1="33.02" x2="378.46" y2="33.02" width="0.1524" layer="91"/>
<wire x1="378.46" y1="33.02" x2="381" y2="33.02" width="0.1524" layer="91"/>
<wire x1="381" y1="33.02" x2="381" y2="30.48" width="0.1524" layer="91"/>
<wire x1="378.46" y1="43.18" x2="378.46" y2="40.64" width="0.1524" layer="91"/>
<junction x="378.46" y="33.02"/>
<wire x1="378.46" y1="40.64" x2="378.46" y2="33.02" width="0.1524" layer="91"/>
<wire x1="365.76" y1="53.34" x2="360.68" y2="53.34" width="0.1524" layer="91"/>
<wire x1="360.68" y1="53.34" x2="360.68" y2="40.64" width="0.1524" layer="91"/>
<wire x1="360.68" y1="40.64" x2="375.92" y2="40.64" width="0.1524" layer="91"/>
<junction x="378.46" y="40.64"/>
<wire x1="375.92" y1="40.64" x2="378.46" y2="40.64" width="0.1524" layer="91"/>
<wire x1="391.16" y1="55.88" x2="393.7" y2="55.88" width="0.1524" layer="91"/>
<wire x1="393.7" y1="55.88" x2="393.7" y2="50.8" width="0.1524" layer="91"/>
<wire x1="393.7" y1="50.8" x2="393.7" y2="40.64" width="0.1524" layer="91"/>
<wire x1="393.7" y1="40.64" x2="381" y2="40.64" width="0.1524" layer="91"/>
<wire x1="381" y1="40.64" x2="378.46" y2="40.64" width="0.1524" layer="91"/>
<wire x1="391.16" y1="50.8" x2="393.7" y2="50.8" width="0.1524" layer="91"/>
<junction x="393.7" y="50.8"/>
<pinref part="U3" gate="G$1" pin="PGND"/>
<pinref part="U3" gate="G$1" pin="PAD"/>
<pinref part="U3" gate="G$1" pin="GND"/>
<pinref part="U3" gate="G$1" pin="PS/S"/>
<pinref part="U3" gate="G$1" pin="VIA2"/>
<wire x1="381" y1="43.18" x2="381" y2="40.64" width="0.1524" layer="91"/>
<junction x="381" y="40.64"/>
<pinref part="U3" gate="G$1" pin="VIA1"/>
<wire x1="375.92" y1="43.18" x2="375.92" y2="40.64" width="0.1524" layer="91"/>
<junction x="375.92" y="40.64"/>
</segment>
<segment>
<pinref part="C2" gate="G$1" pin="P$1"/>
<pinref part="SUPPLY20" gate="GND" pin="GND"/>
<wire x1="375.92" y1="78.74" x2="381" y2="78.74" width="0.1524" layer="91"/>
<wire x1="381" y1="78.74" x2="381" y2="76.2" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="10_GND"/>
<wire x1="337.82" y1="193.04" x2="327.66" y2="193.04" width="0.1524" layer="91"/>
<wire x1="327.66" y1="193.04" x2="327.66" y2="182.88" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="12_GND"/>
<wire x1="327.66" y1="182.88" x2="337.82" y2="182.88" width="0.1524" layer="91"/>
<pinref part="SUPPLY21" gate="GND" pin="GND"/>
<junction x="327.66" y="182.88"/>
<wire x1="327.66" y1="172.72" x2="327.66" y2="182.88" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY22" gate="GND" pin="GND"/>
<pinref part="C3" gate="G$1" pin="P$1"/>
<wire x1="403.86" y1="167.64" x2="403.86" y2="170.18" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="1_GND"/>
<pinref part="SUPPLY23" gate="GND" pin="GND"/>
<wire x1="383.54" y1="152.4" x2="386.08" y2="152.4" width="0.1524" layer="91"/>
<wire x1="386.08" y1="152.4" x2="386.08" y2="149.86" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY25" gate="GND" pin="GND"/>
<wire x1="215.9" y1="149.86" x2="215.9" y2="152.4" width="0.1524" layer="91"/>
<pinref part="U$15" gate="G$1" pin="GND2"/>
</segment>
<segment>
<pinref part="SUPPLY24" gate="GND" pin="GND"/>
<wire x1="251.46" y1="149.86" x2="251.46" y2="152.4" width="0.1524" layer="91"/>
<pinref part="U$15" gate="G$1" pin="GND1"/>
</segment>
<segment>
<pinref part="SUPPLY28" gate="GND" pin="GND"/>
<pinref part="C4" gate="G$1" pin="P$1"/>
<wire x1="139.7" y1="182.88" x2="139.7" y2="185.42" width="0.1524" layer="91"/>
<wire x1="139.7" y1="185.42" x2="139.7" y2="187.96" width="0.1524" layer="91"/>
<wire x1="152.4" y1="195.58" x2="147.32" y2="195.58" width="0.1524" layer="91"/>
<wire x1="147.32" y1="195.58" x2="147.32" y2="185.42" width="0.1524" layer="91"/>
<wire x1="147.32" y1="185.42" x2="139.7" y2="185.42" width="0.1524" layer="91"/>
<junction x="139.7" y="185.42"/>
<pinref part="ME6211-1.8V" gate="G$1" pin="VSS"/>
</segment>
<segment>
<pinref part="SUPPLY29" gate="GND" pin="GND"/>
<pinref part="C5" gate="G$1" pin="P$1"/>
<wire x1="182.88" y1="182.88" x2="182.88" y2="187.96" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY26" gate="GND" pin="GND"/>
<pinref part="C6" gate="G$1" pin="P$1"/>
<wire x1="182.88" y1="149.86" x2="182.88" y2="154.94" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY27" gate="GND" pin="GND"/>
<pinref part="C7" gate="G$1" pin="P$1"/>
<wire x1="139.7" y1="149.86" x2="139.7" y2="152.4" width="0.1524" layer="91"/>
<wire x1="139.7" y1="152.4" x2="139.7" y2="154.94" width="0.1524" layer="91"/>
<wire x1="152.4" y1="162.56" x2="147.32" y2="162.56" width="0.1524" layer="91"/>
<wire x1="147.32" y1="162.56" x2="147.32" y2="152.4" width="0.1524" layer="91"/>
<wire x1="147.32" y1="152.4" x2="139.7" y2="152.4" width="0.1524" layer="91"/>
<junction x="139.7" y="152.4"/>
<pinref part="ME6211-2.8V" gate="G$1" pin="VSS"/>
</segment>
<segment>
<pinref part="SUPPLY30" gate="GND" pin="GND"/>
<pinref part="C8" gate="G$1" pin="P$1"/>
<wire x1="114.3" y1="167.64" x2="114.3" y2="172.72" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C9" gate="G$1" pin="P$1"/>
<wire x1="238.76" y1="215.9" x2="243.84" y2="215.9" width="0.1524" layer="91"/>
<pinref part="SUPPLY31" gate="GND" pin="GND"/>
<wire x1="243.84" y1="215.9" x2="248.92" y2="215.9" width="0.1524" layer="91"/>
<wire x1="248.92" y1="215.9" x2="248.92" y2="213.36" width="0.1524" layer="91"/>
<wire x1="243.84" y1="187.96" x2="243.84" y2="215.9" width="0.1524" layer="91"/>
<junction x="243.84" y="215.9"/>
<pinref part="U$15" gate="G$1" pin="STANDBY"/>
</segment>
<segment>
<pinref part="SUPPLY32" gate="GND" pin="GND"/>
<wire x1="68.58" y1="152.4" x2="73.66" y2="152.4" width="0.1524" layer="91"/>
<wire x1="73.66" y1="152.4" x2="73.66" y2="149.86" width="0.1524" layer="91"/>
<pinref part="R15" gate="G$1" pin="P$2"/>
</segment>
<segment>
<pinref part="R12" gate="G$1" pin="P$2"/>
<pinref part="SUPPLY33" gate="GND" pin="GND"/>
<wire x1="71.12" y1="210.82" x2="73.66" y2="210.82" width="0.1524" layer="91"/>
<wire x1="73.66" y1="210.82" x2="73.66" y2="195.58" width="0.1524" layer="91"/>
<pinref part="R13" gate="G$1" pin="P$2"/>
<wire x1="73.66" y1="195.58" x2="73.66" y2="193.04" width="0.1524" layer="91"/>
<wire x1="71.12" y1="195.58" x2="73.66" y2="195.58" width="0.1524" layer="91"/>
<junction x="73.66" y="195.58"/>
</segment>
<segment>
<pinref part="CFPX-104" gate="G$1" pin="GND1"/>
<wire x1="304.8" y1="276.86" x2="317.5" y2="276.86" width="0.1524" layer="91"/>
<wire x1="317.5" y1="276.86" x2="317.5" y2="274.32" width="0.1524" layer="91"/>
<pinref part="SUPPLY35" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="CFPX-104" gate="G$1" pin="GND2"/>
<wire x1="289.56" y1="281.94" x2="276.86" y2="281.94" width="0.1524" layer="91"/>
<wire x1="276.86" y1="281.94" x2="276.86" y2="279.4" width="0.1524" layer="91"/>
<pinref part="SUPPLY36" gate="GND" pin="GND"/>
</segment>
<segment>
<wire x1="284.48" y1="261.62" x2="284.48" y2="259.08" width="0.1524" layer="91"/>
<pinref part="C10" gate="G$1" pin="P$1"/>
<wire x1="309.88" y1="261.62" x2="309.88" y2="259.08" width="0.1524" layer="91"/>
<wire x1="309.88" y1="259.08" x2="297.18" y2="259.08" width="0.1524" layer="91"/>
<pinref part="SUPPLY34" gate="GND" pin="GND"/>
<wire x1="297.18" y1="259.08" x2="284.48" y2="259.08" width="0.1524" layer="91"/>
<wire x1="297.18" y1="256.54" x2="297.18" y2="259.08" width="0.1524" layer="91"/>
<junction x="297.18" y="259.08"/>
<pinref part="C12" gate="G$1" pin="P$1"/>
</segment>
<segment>
<pinref part="C11" gate="G$1" pin="P$1"/>
<pinref part="SUPPLY37" gate="GND" pin="GND"/>
<wire x1="78.74" y1="350.52" x2="73.66" y2="350.52" width="0.1524" layer="91"/>
<wire x1="73.66" y1="350.52" x2="73.66" y2="337.82" width="0.1524" layer="91"/>
<pinref part="C14" gate="G$1" pin="P$1"/>
<wire x1="73.66" y1="337.82" x2="73.66" y2="325.12" width="0.1524" layer="91"/>
<wire x1="73.66" y1="325.12" x2="73.66" y2="322.58" width="0.1524" layer="91"/>
<wire x1="78.74" y1="325.12" x2="73.66" y2="325.12" width="0.1524" layer="91"/>
<junction x="73.66" y="325.12"/>
<pinref part="C13" gate="G$1" pin="P$1"/>
<wire x1="78.74" y1="337.82" x2="73.66" y2="337.82" width="0.1524" layer="91"/>
<junction x="73.66" y="337.82"/>
</segment>
<segment>
<pinref part="SUPPLY38" gate="GND" pin="GND"/>
<wire x1="73.66" y1="302.26" x2="73.66" y2="304.8" width="0.1524" layer="91"/>
<pinref part="C15" gate="G$1" pin="P$1"/>
<wire x1="73.66" y1="304.8" x2="78.74" y2="304.8" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY39" gate="GND" pin="GND"/>
<wire x1="73.66" y1="281.94" x2="73.66" y2="284.48" width="0.1524" layer="91"/>
<pinref part="C16" gate="G$1" pin="P$1"/>
<wire x1="73.66" y1="284.48" x2="78.74" y2="284.48" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="C18" gate="G$1" pin="P$1"/>
<wire x1="35.56" y1="266.7" x2="30.48" y2="266.7" width="0.1524" layer="91"/>
<wire x1="30.48" y1="266.7" x2="30.48" y2="254" width="0.1524" layer="91"/>
<wire x1="30.48" y1="251.46" x2="30.48" y2="254" width="0.1524" layer="91"/>
<pinref part="C17" gate="G$1" pin="P$1"/>
<wire x1="35.56" y1="254" x2="30.48" y2="254" width="0.1524" layer="91"/>
<junction x="30.48" y="254"/>
<pinref part="SUPPLY40" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="SUPPLY41" gate="GND" pin="GND"/>
<wire x1="30.48" y1="284.48" x2="30.48" y2="287.02" width="0.1524" layer="91"/>
<pinref part="C23" gate="G$1" pin="P$1"/>
<wire x1="30.48" y1="287.02" x2="30.48" y2="299.72" width="0.1524" layer="91"/>
<wire x1="30.48" y1="299.72" x2="30.48" y2="312.42" width="0.1524" layer="91"/>
<wire x1="30.48" y1="312.42" x2="30.48" y2="325.12" width="0.1524" layer="91"/>
<wire x1="30.48" y1="325.12" x2="30.48" y2="337.82" width="0.1524" layer="91"/>
<wire x1="30.48" y1="337.82" x2="30.48" y2="350.52" width="0.1524" layer="91"/>
<wire x1="30.48" y1="350.52" x2="35.56" y2="350.52" width="0.1524" layer="91"/>
<pinref part="C24" gate="G$1" pin="P$1"/>
<wire x1="35.56" y1="337.82" x2="30.48" y2="337.82" width="0.1524" layer="91"/>
<junction x="30.48" y="337.82"/>
<pinref part="C19" gate="G$1" pin="P$1"/>
<wire x1="35.56" y1="325.12" x2="30.48" y2="325.12" width="0.1524" layer="91"/>
<junction x="30.48" y="325.12"/>
<pinref part="C20" gate="G$1" pin="P$1"/>
<wire x1="35.56" y1="312.42" x2="30.48" y2="312.42" width="0.1524" layer="91"/>
<junction x="30.48" y="312.42"/>
<pinref part="C21" gate="G$1" pin="P$1"/>
<wire x1="35.56" y1="299.72" x2="30.48" y2="299.72" width="0.1524" layer="91"/>
<junction x="30.48" y="299.72"/>
<pinref part="C22" gate="G$1" pin="P$1"/>
<wire x1="35.56" y1="287.02" x2="30.48" y2="287.02" width="0.1524" layer="91"/>
<junction x="30.48" y="287.02"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="GND4"/>
<wire x1="195.58" y1="337.82" x2="195.58" y2="358.14" width="0.1524" layer="91"/>
<pinref part="SUPPLY45" gate="GND" pin="GND"/>
<wire x1="195.58" y1="358.14" x2="190.5" y2="358.14" width="0.1524" layer="91"/>
<wire x1="190.5" y1="358.14" x2="190.5" y2="355.6" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="GND3"/>
<pinref part="SUPPLY44" gate="GND" pin="GND"/>
<wire x1="236.22" y1="322.58" x2="254" y2="322.58" width="0.1524" layer="91"/>
<wire x1="254" y1="322.58" x2="254" y2="320.04" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY42" gate="GND" pin="GND"/>
<wire x1="177.8" y1="274.32" x2="177.8" y2="276.86" width="0.1524" layer="91"/>
<pinref part="U4" gate="G$1" pin="GND2"/>
<wire x1="185.42" y1="279.4" x2="185.42" y2="276.86" width="0.1524" layer="91"/>
<wire x1="177.8" y1="276.86" x2="185.42" y2="276.86" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY43" gate="GND" pin="GND"/>
<wire x1="152.4" y1="322.58" x2="152.4" y2="325.12" width="0.1524" layer="91"/>
<pinref part="U4" gate="G$1" pin="GND1"/>
<wire x1="152.4" y1="325.12" x2="170.18" y2="325.12" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="JTAGSEL"/>
<wire x1="220.98" y1="337.82" x2="220.98" y2="358.14" width="0.1524" layer="91"/>
<wire x1="220.98" y1="358.14" x2="226.06" y2="358.14" width="0.1524" layer="91"/>
<wire x1="226.06" y1="358.14" x2="226.06" y2="355.6" width="0.1524" layer="91"/>
<pinref part="SUPPLY46" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="U$10" gate="G$1" pin="GNDH1"/>
<pinref part="SUPPLY47" gate="GND" pin="GND"/>
<wire x1="398.78" y1="332.74" x2="401.32" y2="332.74" width="0.1524" layer="91"/>
<wire x1="401.32" y1="332.74" x2="401.32" y2="330.2" width="0.1524" layer="91"/>
<pinref part="U$10" gate="G$1" pin="GNDH4"/>
<wire x1="401.32" y1="330.2" x2="401.32" y2="327.66" width="0.1524" layer="91"/>
<wire x1="401.32" y1="327.66" x2="401.32" y2="325.12" width="0.1524" layer="91"/>
<wire x1="401.32" y1="325.12" x2="401.32" y2="322.58" width="0.1524" layer="91"/>
<wire x1="398.78" y1="325.12" x2="401.32" y2="325.12" width="0.1524" layer="91"/>
<junction x="401.32" y="325.12"/>
<pinref part="U$10" gate="G$1" pin="GNDH3"/>
<wire x1="398.78" y1="327.66" x2="401.32" y2="327.66" width="0.1524" layer="91"/>
<junction x="401.32" y="327.66"/>
<pinref part="U$10" gate="G$1" pin="GNDH2"/>
<wire x1="398.78" y1="330.2" x2="401.32" y2="330.2" width="0.1524" layer="91"/>
<junction x="401.32" y="330.2"/>
</segment>
<segment>
<pinref part="U$10" gate="G$1" pin="GND"/>
<pinref part="SUPPLY48" gate="GND" pin="GND"/>
<wire x1="373.38" y1="325.12" x2="370.84" y2="325.12" width="0.1524" layer="91"/>
<wire x1="370.84" y1="325.12" x2="370.84" y2="322.58" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY49" gate="GND" pin="GND"/>
<pinref part="C25" gate="G$1" pin="P$1"/>
<wire x1="332.74" y1="353.06" x2="332.74" y2="355.6" width="0.1524" layer="91"/>
<pinref part="C26" gate="G$1" pin="P$1"/>
<wire x1="358.14" y1="355.6" x2="358.14" y2="353.06" width="0.1524" layer="91"/>
<wire x1="358.14" y1="353.06" x2="332.74" y2="353.06" width="0.1524" layer="91"/>
<junction x="332.74" y="353.06"/>
<pinref part="U$9" gate="G$1" pin="GND"/>
<wire x1="337.82" y1="373.38" x2="325.12" y2="373.38" width="0.1524" layer="91"/>
<wire x1="325.12" y1="373.38" x2="325.12" y2="353.06" width="0.1524" layer="91"/>
<wire x1="325.12" y1="353.06" x2="332.74" y2="353.06" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="JP4" gate="G$1" pin="2"/>
<wire x1="355.6" y1="284.48" x2="342.9" y2="284.48" width="0.1524" layer="91"/>
<label x="342.9" y="284.48" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="JP2" gate="G$1" pin="2"/>
<wire x1="393.7" y1="254" x2="381" y2="254" width="0.1524" layer="91"/>
<label x="381" y="254" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="SUPPLY52" gate="GND" pin="GND"/>
<wire x1="86.36" y1="12.7" x2="86.36" y2="15.24" width="0.1524" layer="91"/>
<pinref part="RH" gate="G$1" pin="P$1"/>
<wire x1="86.36" y1="15.24" x2="88.9" y2="15.24" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="SUPPLY9" gate="GND" pin="GND"/>
<pinref part="RF-1" gate="G$1" pin="P$1"/>
<wire x1="55.88" y1="78.74" x2="55.88" y2="81.28" width="0.1524" layer="91"/>
<wire x1="55.88" y1="81.28" x2="55.88" y2="83.82" width="0.1524" layer="91"/>
<wire x1="55.88" y1="81.28" x2="71.12" y2="81.28" width="0.1524" layer="91"/>
<junction x="55.88" y="81.28"/>
<pinref part="RF-2" gate="G$1" pin="P$1"/>
<wire x1="71.12" y1="81.28" x2="71.12" y2="83.82" width="0.1524" layer="91"/>
</segment>
<segment>
<pinref part="U$1" gate="G$1" pin="GNDV2"/>
<wire x1="187.96" y1="78.74" x2="190.5" y2="78.74" width="0.1524" layer="91"/>
<wire x1="190.5" y1="78.74" x2="190.5" y2="48.26" width="0.1524" layer="91"/>
<wire x1="190.5" y1="48.26" x2="195.58" y2="48.26" width="0.1524" layer="91"/>
<pinref part="SUPPLY5" gate="GND" pin="GND"/>
<wire x1="195.58" y1="48.26" x2="195.58" y2="45.72" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="GNDV1"/>
<wire x1="187.96" y1="43.18" x2="190.5" y2="43.18" width="0.1524" layer="91"/>
<wire x1="190.5" y1="43.18" x2="190.5" y2="48.26" width="0.1524" layer="91"/>
<junction x="190.5" y="48.26"/>
</segment>
</net>
<net name="GPIO1" class="0">
<segment>
<wire x1="175.26" y1="38.1" x2="175.26" y2="35.56" width="0.1524" layer="91"/>
<wire x1="175.26" y1="35.56" x2="200.66" y2="35.56" width="0.1524" layer="91"/>
<label x="195.58" y="35.56" size="1.778" layer="95"/>
<pinref part="U$1" gate="G$1" pin="GPIO1"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PB4"/>
<wire x1="236.22" y1="289.56" x2="246.38" y2="289.56" width="0.1524" layer="91"/>
<label x="238.76" y="289.56" size="1.778" layer="95"/>
</segment>
</net>
<net name="SDN" class="0">
<segment>
<wire x1="142.24" y1="71.12" x2="129.54" y2="71.12" width="0.1524" layer="91"/>
<wire x1="129.54" y1="71.12" x2="129.54" y2="81.28" width="0.1524" layer="91"/>
<pinref part="R1" gate="G$1" pin="P$1"/>
<wire x1="129.54" y1="81.28" x2="127" y2="81.28" width="0.1524" layer="91"/>
<wire x1="129.54" y1="71.12" x2="119.38" y2="71.12" width="0.1524" layer="91"/>
<junction x="129.54" y="71.12"/>
<label x="119.38" y="71.12" size="1.778" layer="95"/>
<pinref part="U$1" gate="G$1" pin="SDN"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA7"/>
<wire x1="223.52" y1="279.4" x2="223.52" y2="269.24" width="0.1524" layer="91"/>
<label x="223.52" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="N$9" class="0">
<segment>
<pinref part="TCXO" gate="G$1" pin="OUT"/>
<wire x1="162.56" y1="111.76" x2="170.18" y2="111.76" width="0.1524" layer="91"/>
<wire x1="170.18" y1="111.76" x2="170.18" y2="83.82" width="0.1524" layer="91"/>
<pinref part="U$1" gate="G$1" pin="XIN"/>
</segment>
</net>
<net name="3.3V" class="0">
<segment>
<pinref part="CD4" gate="G$1" pin="P$2"/>
<wire x1="182.88" y1="27.94" x2="182.88" y2="30.48" width="0.1524" layer="91"/>
<wire x1="182.88" y1="30.48" x2="170.18" y2="30.48" width="0.1524" layer="91"/>
<pinref part="CD1" gate="G$1" pin="P$2"/>
<wire x1="170.18" y1="30.48" x2="144.78" y2="30.48" width="0.1524" layer="91"/>
<wire x1="144.78" y1="30.48" x2="144.78" y2="27.94" width="0.1524" layer="91"/>
<pinref part="CD3" gate="G$1" pin="P$2"/>
<wire x1="170.18" y1="27.94" x2="170.18" y2="30.48" width="0.1524" layer="91"/>
<junction x="170.18" y="30.48"/>
<wire x1="165.1" y1="38.1" x2="165.1" y2="35.56" width="0.1524" layer="91"/>
<wire x1="154.94" y1="38.1" x2="154.94" y2="35.56" width="0.1524" layer="91"/>
<wire x1="154.94" y1="35.56" x2="165.1" y2="35.56" width="0.1524" layer="91"/>
<wire x1="154.94" y1="35.56" x2="144.78" y2="35.56" width="0.1524" layer="91"/>
<junction x="154.94" y="35.56"/>
<wire x1="144.78" y1="35.56" x2="144.78" y2="30.48" width="0.1524" layer="91"/>
<junction x="144.78" y="30.48"/>
<pinref part="LCHOKE" gate="G$1" pin="P$1"/>
<wire x1="129.54" y1="30.48" x2="144.78" y2="30.48" width="0.1524" layer="91"/>
<wire x1="129.54" y1="30.48" x2="129.54" y2="17.78" width="0.1524" layer="91"/>
<junction x="129.54" y="30.48"/>
<label x="124.46" y="17.78" size="1.778" layer="95"/>
<pinref part="U$1" gate="G$1" pin="VDD1"/>
<pinref part="U$1" gate="G$1" pin="VDD2"/>
</segment>
<segment>
<wire x1="365.76" y1="58.42" x2="363.22" y2="58.42" width="0.1524" layer="91"/>
<wire x1="363.22" y1="58.42" x2="363.22" y2="66.04" width="0.1524" layer="91"/>
<wire x1="363.22" y1="66.04" x2="363.22" y2="78.74" width="0.1524" layer="91"/>
<wire x1="363.22" y1="78.74" x2="363.22" y2="88.9" width="0.1524" layer="91"/>
<wire x1="363.22" y1="88.9" x2="373.38" y2="88.9" width="0.1524" layer="91"/>
<pinref part="C2" gate="G$1" pin="P$2"/>
<wire x1="365.76" y1="78.74" x2="363.22" y2="78.74" width="0.1524" layer="91"/>
<junction x="363.22" y="78.74"/>
<label x="368.3" y="88.9" size="1.778" layer="95"/>
<wire x1="391.16" y1="58.42" x2="391.16" y2="66.04" width="0.1524" layer="91"/>
<wire x1="391.16" y1="66.04" x2="363.22" y2="66.04" width="0.1524" layer="91"/>
<junction x="363.22" y="66.04"/>
<pinref part="U3" gate="G$1" pin="VOUT"/>
<pinref part="U3" gate="G$1" pin="FB"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="7_VCC_IO"/>
<wire x1="383.54" y1="182.88" x2="386.08" y2="182.88" width="0.1524" layer="91"/>
<wire x1="386.08" y1="182.88" x2="386.08" y2="187.96" width="0.1524" layer="91"/>
<pinref part="U$2" gate="G$1" pin="6_V_BCKP"/>
<wire x1="383.54" y1="177.8" x2="386.08" y2="177.8" width="0.1524" layer="91"/>
<wire x1="386.08" y1="177.8" x2="386.08" y2="182.88" width="0.1524" layer="91"/>
<junction x="386.08" y="182.88"/>
<pinref part="U$2" gate="G$1" pin="8_VCC"/>
<wire x1="383.54" y1="187.96" x2="386.08" y2="187.96" width="0.1524" layer="91"/>
<wire x1="386.08" y1="182.88" x2="403.86" y2="182.88" width="0.1524" layer="91"/>
<pinref part="C3" gate="G$1" pin="P$2"/>
<wire x1="411.48" y1="182.88" x2="403.86" y2="182.88" width="0.1524" layer="91"/>
<wire x1="403.86" y1="182.88" x2="403.86" y2="180.34" width="0.1524" layer="91"/>
<label x="406.4" y="182.88" size="1.778" layer="95"/>
<junction x="403.86" y="182.88"/>
</segment>
<segment>
<pinref part="C4" gate="G$1" pin="P$2"/>
<wire x1="152.4" y1="200.66" x2="149.86" y2="200.66" width="0.1524" layer="91"/>
<wire x1="149.86" y1="200.66" x2="139.7" y2="200.66" width="0.1524" layer="91"/>
<wire x1="139.7" y1="200.66" x2="139.7" y2="198.12" width="0.1524" layer="91"/>
<wire x1="139.7" y1="200.66" x2="129.54" y2="200.66" width="0.1524" layer="91"/>
<junction x="139.7" y="200.66"/>
<label x="129.54" y="200.66" size="1.778" layer="95"/>
<wire x1="152.4" y1="190.5" x2="149.86" y2="190.5" width="0.1524" layer="91"/>
<wire x1="149.86" y1="190.5" x2="149.86" y2="200.66" width="0.1524" layer="91"/>
<junction x="149.86" y="200.66"/>
<pinref part="ME6211-1.8V" gate="G$1" pin="VIN"/>
<pinref part="ME6211-1.8V" gate="G$1" pin="CE"/>
</segment>
<segment>
<pinref part="C7" gate="G$1" pin="P$2"/>
<wire x1="139.7" y1="165.1" x2="139.7" y2="167.64" width="0.1524" layer="91"/>
<wire x1="139.7" y1="167.64" x2="149.86" y2="167.64" width="0.1524" layer="91"/>
<wire x1="149.86" y1="167.64" x2="152.4" y2="167.64" width="0.1524" layer="91"/>
<wire x1="139.7" y1="167.64" x2="129.54" y2="167.64" width="0.1524" layer="91"/>
<junction x="139.7" y="167.64"/>
<label x="129.54" y="167.64" size="1.778" layer="95"/>
<wire x1="152.4" y1="157.48" x2="149.86" y2="157.48" width="0.1524" layer="91"/>
<wire x1="149.86" y1="157.48" x2="149.86" y2="167.64" width="0.1524" layer="91"/>
<junction x="149.86" y="167.64"/>
<pinref part="ME6211-2.8V" gate="G$1" pin="VIN"/>
<pinref part="ME6211-2.8V" gate="G$1" pin="CE"/>
</segment>
<segment>
<pinref part="C8" gate="G$1" pin="P$2"/>
<wire x1="114.3" y1="182.88" x2="114.3" y2="193.04" width="0.1524" layer="91"/>
<label x="114.3" y="193.04" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="215.9" y1="187.96" x2="215.9" y2="198.12" width="0.1524" layer="91"/>
<label x="215.9" y="193.04" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="MOTOR+"/>
</segment>
<segment>
<pinref part="C15" gate="G$1" pin="P$2"/>
<wire x1="88.9" y1="304.8" x2="101.6" y2="304.8" width="0.1524" layer="91"/>
<label x="96.52" y="304.8" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="VDDIN"/>
<wire x1="170.18" y1="312.42" x2="157.48" y2="312.42" width="0.1524" layer="91"/>
<label x="157.48" y="312.42" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="C22" gate="G$1" pin="P$2"/>
<wire x1="45.72" y1="287.02" x2="50.8" y2="287.02" width="0.1524" layer="91"/>
<wire x1="50.8" y1="287.02" x2="50.8" y2="299.72" width="0.1524" layer="91"/>
<pinref part="C23" gate="G$1" pin="P$2"/>
<wire x1="50.8" y1="299.72" x2="50.8" y2="312.42" width="0.1524" layer="91"/>
<wire x1="50.8" y1="312.42" x2="50.8" y2="325.12" width="0.1524" layer="91"/>
<wire x1="50.8" y1="325.12" x2="50.8" y2="337.82" width="0.1524" layer="91"/>
<wire x1="50.8" y1="337.82" x2="50.8" y2="350.52" width="0.1524" layer="91"/>
<wire x1="50.8" y1="350.52" x2="45.72" y2="350.52" width="0.1524" layer="91"/>
<wire x1="50.8" y1="350.52" x2="63.5" y2="350.52" width="0.1524" layer="91"/>
<junction x="50.8" y="350.52"/>
<pinref part="C24" gate="G$1" pin="P$2"/>
<wire x1="45.72" y1="337.82" x2="50.8" y2="337.82" width="0.1524" layer="91"/>
<junction x="50.8" y="337.82"/>
<pinref part="C19" gate="G$1" pin="P$2"/>
<wire x1="45.72" y1="325.12" x2="50.8" y2="325.12" width="0.1524" layer="91"/>
<junction x="50.8" y="325.12"/>
<pinref part="C20" gate="G$1" pin="P$2"/>
<wire x1="45.72" y1="312.42" x2="50.8" y2="312.42" width="0.1524" layer="91"/>
<junction x="50.8" y="312.42"/>
<pinref part="C21" gate="G$1" pin="P$2"/>
<wire x1="45.72" y1="299.72" x2="50.8" y2="299.72" width="0.1524" layer="91"/>
<junction x="50.8" y="299.72"/>
<label x="58.42" y="350.52" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="VDDIO1"/>
<wire x1="187.96" y1="279.4" x2="187.96" y2="266.7" width="0.1524" layer="91"/>
<label x="187.96" y="266.7" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="VDDIO2"/>
<wire x1="236.22" y1="320.04" x2="248.92" y2="320.04" width="0.1524" layer="91"/>
<label x="243.84" y="320.04" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="VDDIO3"/>
<wire x1="200.66" y1="337.82" x2="200.66" y2="350.52" width="0.1524" layer="91"/>
<label x="200.66" y="345.44" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="U$9" gate="G$1" pin="VOUT"/>
<wire x1="337.82" y1="368.3" x2="332.74" y2="368.3" width="0.1524" layer="91"/>
<pinref part="C25" gate="G$1" pin="P$2"/>
<wire x1="332.74" y1="368.3" x2="332.74" y2="365.76" width="0.1524" layer="91"/>
<wire x1="332.74" y1="368.3" x2="312.42" y2="368.3" width="0.1524" layer="91"/>
<junction x="332.74" y="368.3"/>
<label x="312.42" y="368.3" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="JP4" gate="G$1" pin="1"/>
<wire x1="355.6" y1="287.02" x2="342.9" y2="287.02" width="0.1524" layer="91"/>
<label x="342.9" y="287.02" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="JP2" gate="G$1" pin="1"/>
<wire x1="393.7" y1="256.54" x2="381" y2="256.54" width="0.1524" layer="91"/>
<label x="381" y="256.54" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="ADVREF"/>
<wire x1="170.18" y1="327.66" x2="157.48" y2="327.66" width="0.1524" layer="91"/>
<label x="157.48" y="327.66" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="LCHOKE" gate="G$1" pin="P$2"/>
<wire x1="142.24" y1="55.88" x2="129.54" y2="55.88" width="0.1524" layer="91"/>
<wire x1="129.54" y1="55.88" x2="129.54" y2="53.34" width="0.1524" layer="91"/>
<pinref part="C0" gate="G$1" pin="P$2"/>
<wire x1="129.54" y1="53.34" x2="129.54" y2="45.72" width="0.1524" layer="91"/>
<wire x1="127" y1="53.34" x2="129.54" y2="53.34" width="0.1524" layer="91"/>
<junction x="129.54" y="53.34"/>
<pinref part="U$1" gate="G$1" pin="TX"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="LM1" gate="G$1" pin="P$2"/>
<wire x1="83.82" y1="53.34" x2="86.36" y2="53.34" width="0.1524" layer="91"/>
<junction x="86.36" y="53.34"/>
<pinref part="CM" gate="G$1" pin="P$2"/>
<wire x1="86.36" y1="45.72" x2="86.36" y2="53.34" width="0.1524" layer="91"/>
<pinref part="L0" gate="G$1" pin="P$1"/>
<wire x1="86.36" y1="53.34" x2="91.44" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$7" class="0">
<segment>
<pinref part="LM1" gate="G$1" pin="P$1"/>
<pinref part="LM2" gate="G$1" pin="P$2"/>
<wire x1="68.58" y1="53.34" x2="66.04" y2="53.34" width="0.1524" layer="91"/>
<pinref part="CM1" gate="G$1" pin="P$2"/>
<wire x1="66.04" y1="53.34" x2="63.5" y2="53.34" width="0.1524" layer="91"/>
<wire x1="66.04" y1="45.72" x2="66.04" y2="53.34" width="0.1524" layer="91"/>
<junction x="66.04" y="53.34"/>
</segment>
</net>
<net name="N$8" class="0">
<segment>
<pinref part="LM2" gate="G$1" pin="P$1"/>
<wire x1="48.26" y1="53.34" x2="45.72" y2="53.34" width="0.1524" layer="91"/>
<pinref part="CM2" gate="G$1" pin="P$2"/>
<wire x1="45.72" y1="45.72" x2="45.72" y2="53.34" width="0.1524" layer="91"/>
<wire x1="43.18" y1="53.34" x2="45.72" y2="53.34" width="0.1524" layer="91"/>
<junction x="45.72" y="53.34"/>
<pinref part="LM3" gate="G$1" pin="P$2"/>
</segment>
</net>
<net name="N$12" class="0">
<segment>
<wire x1="22.86" y1="53.34" x2="27.94" y2="53.34" width="0.1524" layer="91"/>
<pinref part="RF+" gate="G$1" pin="P$1"/>
<pinref part="LM3" gate="G$1" pin="P$1"/>
</segment>
</net>
<net name="SOLAR+" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="VIN"/>
<wire x1="284.48" y1="50.8" x2="287.02" y2="50.8" width="0.1524" layer="91"/>
<wire x1="287.02" y1="50.8" x2="287.02" y2="35.56" width="0.1524" layer="91"/>
<wire x1="287.02" y1="35.56" x2="284.48" y2="35.56" width="0.1524" layer="91"/>
<junction x="287.02" y="35.56"/>
<pinref part="LTC-10UH" gate="G$1" pin="P$2"/>
<wire x1="297.18" y1="38.1" x2="297.18" y2="35.56" width="0.1524" layer="91"/>
<wire x1="297.18" y1="35.56" x2="287.02" y2="35.56" width="0.1524" layer="91"/>
<pinref part="CIN" gate="G$1" pin="P$2"/>
</segment>
<segment>
<pinref part="R9" gate="G$1" pin="P$1"/>
<wire x1="50.8" y1="172.72" x2="40.64" y2="172.72" width="0.1524" layer="91"/>
<label x="40.64" y="172.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$11" class="0">
<segment>
<pinref part="LTC-10UH" gate="G$1" pin="P$1"/>
<wire x1="297.18" y1="53.34" x2="297.18" y2="55.88" width="0.1524" layer="91"/>
<wire x1="297.18" y1="55.88" x2="289.56" y2="55.88" width="0.1524" layer="91"/>
<wire x1="289.56" y1="55.88" x2="289.56" y2="53.34" width="0.1524" layer="91"/>
<pinref part="U1" gate="G$1" pin="SW"/>
<wire x1="289.56" y1="53.34" x2="284.48" y2="53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$14" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="MPPC"/>
<pinref part="R5" gate="G$1" pin="P$2"/>
<wire x1="254" y1="50.8" x2="241.3" y2="50.8" width="0.1524" layer="91"/>
<wire x1="241.3" y1="50.8" x2="241.3" y2="48.26" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$13" class="0">
<segment>
<pinref part="LDO" gate="G$1" pin="P$2"/>
<pinref part="U1" gate="G$1" pin="LDO"/>
<wire x1="246.38" y1="58.42" x2="254" y2="58.42" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$15" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="AUX"/>
<wire x1="284.48" y1="60.96" x2="287.02" y2="60.96" width="0.1524" layer="91"/>
<wire x1="287.02" y1="60.96" x2="287.02" y2="73.66" width="0.1524" layer="91"/>
<wire x1="287.02" y1="73.66" x2="279.4" y2="73.66" width="0.1524" layer="91"/>
<pinref part="AUX" gate="G$1" pin="P$2"/>
</segment>
</net>
<net name="4.2V" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="VOUT"/>
<wire x1="284.48" y1="58.42" x2="292.1" y2="58.42" width="0.1524" layer="91"/>
<wire x1="292.1" y1="58.42" x2="292.1" y2="66.04" width="0.1524" layer="91"/>
<pinref part="COUT" gate="G$1" pin="P$1"/>
<wire x1="292.1" y1="66.04" x2="292.1" y2="78.74" width="0.1524" layer="91"/>
<wire x1="292.1" y1="78.74" x2="292.1" y2="88.9" width="0.1524" layer="91"/>
<wire x1="292.1" y1="66.04" x2="294.64" y2="66.04" width="0.1524" layer="91"/>
<junction x="292.1" y="66.04"/>
<pinref part="R3" gate="G$1" pin="P$2"/>
<wire x1="292.1" y1="88.9" x2="281.94" y2="88.9" width="0.1524" layer="91"/>
<wire x1="292.1" y1="78.74" x2="312.42" y2="78.74" width="0.1524" layer="91"/>
<junction x="292.1" y="78.74"/>
<wire x1="312.42" y1="78.74" x2="312.42" y2="71.12" width="0.1524" layer="91"/>
<label x="307.34" y="71.12" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$17" class="0">
<segment>
<pinref part="R3" gate="G$1" pin="P$1"/>
<pinref part="R4" gate="G$1" pin="P$2"/>
<wire x1="266.7" y1="88.9" x2="259.08" y2="88.9" width="0.1524" layer="91"/>
<wire x1="254" y1="88.9" x2="259.08" y2="88.9" width="0.1524" layer="91"/>
<wire x1="259.08" y1="88.9" x2="259.08" y2="81.28" width="0.1524" layer="91"/>
<wire x1="259.08" y1="81.28" x2="251.46" y2="81.28" width="0.1524" layer="91"/>
<wire x1="251.46" y1="81.28" x2="251.46" y2="60.96" width="0.1524" layer="91"/>
<pinref part="U1" gate="G$1" pin="FB"/>
<wire x1="251.46" y1="60.96" x2="254" y2="60.96" width="0.1524" layer="91"/>
<junction x="259.08" y="88.9"/>
</segment>
</net>
<net name="N$10" class="0">
<segment>
<pinref part="L1" gate="G$1" pin="P$1"/>
<wire x1="350.52" y1="45.72" x2="350.52" y2="43.18" width="0.1524" layer="91"/>
<wire x1="350.52" y1="43.18" x2="358.14" y2="43.18" width="0.1524" layer="91"/>
<wire x1="358.14" y1="43.18" x2="358.14" y2="50.8" width="0.1524" layer="91"/>
<wire x1="358.14" y1="50.8" x2="365.76" y2="50.8" width="0.1524" layer="91"/>
<pinref part="U3" gate="G$1" pin="L1"/>
</segment>
</net>
<net name="N$16" class="0">
<segment>
<wire x1="365.76" y1="55.88" x2="358.14" y2="55.88" width="0.1524" layer="91"/>
<wire x1="358.14" y1="55.88" x2="358.14" y2="63.5" width="0.1524" layer="91"/>
<pinref part="L1" gate="G$1" pin="P$2"/>
<wire x1="358.14" y1="63.5" x2="350.52" y2="63.5" width="0.1524" layer="91"/>
<wire x1="350.52" y1="63.5" x2="350.52" y2="60.96" width="0.1524" layer="91"/>
<pinref part="U3" gate="G$1" pin="L2"/>
</segment>
</net>
<net name="N$18" class="0">
<segment>
<pinref part="U$2" gate="G$1" pin="11_RF_IN"/>
<pinref part="RF_IN+" gate="G$1" pin="P$1"/>
<wire x1="337.82" y1="187.96" x2="317.5" y2="187.96" width="0.1524" layer="91"/>
</segment>
</net>
<net name="D0" class="0">
<segment>
<wire x1="243.84" y1="152.4" x2="243.84" y2="144.78" width="0.1524" layer="91"/>
<label x="243.84" y="144.78" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="D0"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA24"/>
<wire x1="200.66" y1="279.4" x2="200.66" y2="269.24" width="0.1524" layer="91"/>
<label x="200.66" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="D1" class="0">
<segment>
<wire x1="241.3" y1="152.4" x2="241.3" y2="144.78" width="0.1524" layer="91"/>
<label x="241.3" y="144.78" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="D1"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA25"/>
<wire x1="205.74" y1="279.4" x2="205.74" y2="269.24" width="0.1524" layer="91"/>
<label x="205.74" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="D2" class="0">
<segment>
<wire x1="238.76" y1="152.4" x2="238.76" y2="144.78" width="0.1524" layer="91"/>
<label x="238.76" y="144.78" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="D2"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA26"/>
<wire x1="208.28" y1="279.4" x2="208.28" y2="269.24" width="0.1524" layer="91"/>
<label x="208.28" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="D3" class="0">
<segment>
<wire x1="236.22" y1="152.4" x2="236.22" y2="144.78" width="0.1524" layer="91"/>
<label x="236.22" y="144.78" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="D3"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA27"/>
<wire x1="236.22" y1="299.72" x2="246.38" y2="299.72" width="0.1524" layer="91"/>
<label x="243.84" y="299.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="D4" class="0">
<segment>
<wire x1="233.68" y1="152.4" x2="233.68" y2="144.78" width="0.1524" layer="91"/>
<label x="233.68" y="144.78" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="D4"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA28"/>
<wire x1="236.22" y1="302.26" x2="246.38" y2="302.26" width="0.1524" layer="91"/>
<label x="243.84" y="302.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="D5" class="0">
<segment>
<wire x1="231.14" y1="152.4" x2="231.14" y2="144.78" width="0.1524" layer="91"/>
<label x="231.14" y="144.78" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="D5"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA29"/>
<wire x1="236.22" y1="309.88" x2="246.38" y2="309.88" width="0.1524" layer="91"/>
<label x="243.84" y="309.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="D6" class="0">
<segment>
<wire x1="228.6" y1="152.4" x2="228.6" y2="144.78" width="0.1524" layer="91"/>
<label x="228.6" y="144.78" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="D6"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA30"/>
<wire x1="236.22" y1="312.42" x2="246.38" y2="312.42" width="0.1524" layer="91"/>
<label x="243.84" y="312.42" size="1.778" layer="95"/>
</segment>
</net>
<net name="D7" class="0">
<segment>
<wire x1="226.06" y1="152.4" x2="226.06" y2="144.78" width="0.1524" layer="91"/>
<label x="226.06" y="144.78" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="D7"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA31"/>
<wire x1="215.9" y1="337.82" x2="215.9" y2="347.98" width="0.1524" layer="91"/>
<label x="215.9" y="345.44" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="2.8V" class="0">
<segment>
<pinref part="C6" gate="G$1" pin="P$2"/>
<wire x1="172.72" y1="167.64" x2="182.88" y2="167.64" width="0.1524" layer="91"/>
<wire x1="182.88" y1="167.64" x2="182.88" y2="165.1" width="0.1524" layer="91"/>
<wire x1="182.88" y1="167.64" x2="190.5" y2="167.64" width="0.1524" layer="91"/>
<junction x="182.88" y="167.64"/>
<label x="185.42" y="167.64" size="1.778" layer="95"/>
<pinref part="ME6211-2.8V" gate="G$1" pin="VOUT"/>
</segment>
<segment>
<wire x1="218.44" y1="187.96" x2="218.44" y2="190.5" width="0.1524" layer="91"/>
<wire x1="218.44" y1="190.5" x2="220.98" y2="190.5" width="0.1524" layer="91"/>
<wire x1="220.98" y1="190.5" x2="220.98" y2="198.12" width="0.1524" layer="91"/>
<wire x1="220.98" y1="187.96" x2="220.98" y2="190.5" width="0.1524" layer="91"/>
<junction x="220.98" y="190.5"/>
<label x="220.98" y="193.04" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="VDDPLL"/>
<pinref part="U$15" gate="G$1" pin="VDDQ"/>
</segment>
<segment>
<pinref part="R6" gate="G$1" pin="P$1"/>
<wire x1="208.28" y1="208.28" x2="200.66" y2="208.28" width="0.1524" layer="91"/>
<label x="200.66" y="208.28" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="R8" gate="G$1" pin="P$2"/>
<wire x1="271.78" y1="190.5" x2="274.32" y2="190.5" width="0.1524" layer="91"/>
<wire x1="274.32" y1="190.5" x2="274.32" y2="213.36" width="0.1524" layer="91"/>
<pinref part="R7" gate="G$1" pin="P$2"/>
<wire x1="274.32" y1="213.36" x2="271.78" y2="213.36" width="0.1524" layer="91"/>
<wire x1="274.32" y1="190.5" x2="274.32" y2="180.34" width="0.1524" layer="91"/>
<junction x="274.32" y="190.5"/>
<wire x1="274.32" y1="180.34" x2="266.7" y2="180.34" width="0.1524" layer="91"/>
<label x="266.7" y="177.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="1.8V" class="0">
<segment>
<pinref part="C5" gate="G$1" pin="P$2"/>
<wire x1="172.72" y1="200.66" x2="182.88" y2="200.66" width="0.1524" layer="91"/>
<wire x1="182.88" y1="200.66" x2="182.88" y2="198.12" width="0.1524" layer="91"/>
<wire x1="182.88" y1="200.66" x2="190.5" y2="200.66" width="0.1524" layer="91"/>
<junction x="182.88" y="200.66"/>
<label x="185.42" y="200.66" size="1.778" layer="95"/>
<pinref part="ME6211-1.8V" gate="G$1" pin="VOUT"/>
</segment>
<segment>
<wire x1="238.76" y1="187.96" x2="238.76" y2="198.12" width="0.1524" layer="91"/>
<label x="238.76" y="193.04" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="VDD"/>
</segment>
</net>
<net name="PCLK" class="0">
<segment>
<wire x1="241.3" y1="187.96" x2="241.3" y2="198.12" width="0.1524" layer="91"/>
<label x="241.3" y="193.04" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="PIXCLK"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA23"/>
<wire x1="170.18" y1="292.1" x2="160.02" y2="292.1" width="0.1524" layer="91"/>
<label x="160.02" y="292.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="CLK" class="0">
<segment>
<wire x1="236.22" y1="187.96" x2="236.22" y2="198.12" width="0.1524" layer="91"/>
<label x="236.22" y="193.04" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="CLK"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PB13"/>
<wire x1="198.12" y1="337.82" x2="198.12" y2="347.98" width="0.1524" layer="91"/>
<label x="198.12" y="342.9" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="HREF" class="0">
<segment>
<wire x1="228.6" y1="187.96" x2="228.6" y2="198.12" width="0.1524" layer="91"/>
<label x="228.6" y="193.04" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="LINE_VALID"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA16"/>
<wire x1="190.5" y1="279.4" x2="190.5" y2="269.24" width="0.1524" layer="91"/>
<label x="190.5" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="VSYNC" class="0">
<segment>
<wire x1="231.14" y1="187.96" x2="231.14" y2="198.12" width="0.1524" layer="91"/>
<label x="231.14" y="193.04" size="1.778" layer="95" rot="R90"/>
<pinref part="U$15" gate="G$1" pin="FRAME_VALID"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA15"/>
<wire x1="193.04" y1="279.4" x2="193.04" y2="269.24" width="0.1524" layer="91"/>
<label x="193.04" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="N$21" class="0">
<segment>
<wire x1="233.68" y1="187.96" x2="233.68" y2="208.28" width="0.1524" layer="91"/>
<pinref part="R6" gate="G$1" pin="P$2"/>
<wire x1="233.68" y1="208.28" x2="226.06" y2="208.28" width="0.1524" layer="91"/>
<wire x1="226.06" y1="208.28" x2="223.52" y2="208.28" width="0.1524" layer="91"/>
<wire x1="226.06" y1="208.28" x2="226.06" y2="215.9" width="0.1524" layer="91"/>
<junction x="226.06" y="208.28"/>
<pinref part="C9" gate="G$1" pin="P$2"/>
<wire x1="226.06" y1="215.9" x2="228.6" y2="215.9" width="0.1524" layer="91"/>
<pinref part="U$15" gate="G$1" pin="RESET_BAR"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="CATHODE"/>
<pinref part="R12" gate="G$1" pin="P$1"/>
<wire x1="50.8" y1="210.82" x2="55.88" y2="210.82" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$25" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="CATHODE"/>
<pinref part="R13" gate="G$1" pin="P$1"/>
<wire x1="50.8" y1="195.58" x2="55.88" y2="195.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="LEDB" class="0">
<segment>
<pinref part="U$4" gate="G$1" pin="ANODE"/>
<wire x1="40.64" y1="195.58" x2="30.48" y2="195.58" width="0.1524" layer="91"/>
<label x="30.48" y="195.58" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PA0"/>
<wire x1="236.22" y1="327.66" x2="246.38" y2="327.66" width="0.1524" layer="91"/>
<label x="238.76" y="327.66" size="1.778" layer="95"/>
</segment>
</net>
<net name="LEDG" class="0">
<segment>
<pinref part="U$3" gate="G$1" pin="ANODE"/>
<wire x1="40.64" y1="210.82" x2="30.48" y2="210.82" width="0.1524" layer="91"/>
<label x="30.48" y="210.82" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="PB5"/>
<wire x1="223.52" y1="337.82" x2="223.52" y2="347.98" width="0.1524" layer="91"/>
<label x="223.52" y="340.36" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="XIN" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="XIN"/>
<wire x1="190.5" y1="337.82" x2="190.5" y2="345.44" width="0.1524" layer="91"/>
<label x="190.5" y="340.36" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="CFPX-104" gate="G$1" pin="XTAL1"/>
<wire x1="289.56" y1="276.86" x2="284.48" y2="276.86" width="0.1524" layer="91"/>
<wire x1="284.48" y1="276.86" x2="284.48" y2="271.78" width="0.1524" layer="91"/>
<wire x1="284.48" y1="276.86" x2="284.48" y2="294.64" width="0.1524" layer="91"/>
<junction x="284.48" y="276.86"/>
<label x="284.48" y="289.56" size="1.778" layer="95" rot="R90"/>
<pinref part="C12" gate="G$1" pin="P$2"/>
</segment>
</net>
<net name="XOUT" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="XOUT"/>
<wire x1="193.04" y1="337.82" x2="193.04" y2="345.44" width="0.1524" layer="91"/>
<label x="193.04" y="340.36" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="CFPX-104" gate="G$1" pin="XTAL2"/>
<wire x1="304.8" y1="281.94" x2="309.88" y2="281.94" width="0.1524" layer="91"/>
<pinref part="C10" gate="G$1" pin="P$2"/>
<wire x1="309.88" y1="281.94" x2="309.88" y2="271.78" width="0.1524" layer="91"/>
<wire x1="309.88" y1="281.94" x2="309.88" y2="294.64" width="0.1524" layer="91"/>
<junction x="309.88" y="281.94"/>
<label x="309.88" y="289.56" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="NRST" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="NRST"/>
<wire x1="236.22" y1="304.8" x2="243.84" y2="304.8" width="0.1524" layer="91"/>
<label x="238.76" y="304.8" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="JP3" gate="G$1" pin="2"/>
<wire x1="355.6" y1="269.24" x2="342.9" y2="269.24" width="0.1524" layer="91"/>
<label x="342.9" y="269.24" size="1.778" layer="95"/>
</segment>
</net>
<net name="ERASE" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PB12"/>
<wire x1="208.28" y1="337.82" x2="208.28" y2="345.44" width="0.1524" layer="91"/>
<label x="208.28" y="340.36" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="JP3" gate="G$1" pin="1"/>
<wire x1="355.6" y1="271.78" x2="342.9" y2="271.78" width="0.1524" layer="91"/>
<label x="342.9" y="271.78" size="1.778" layer="95"/>
</segment>
</net>
<net name="UTXD0" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA10"/>
<wire x1="215.9" y1="279.4" x2="215.9" y2="269.24" width="0.1524" layer="91"/>
<label x="215.9" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="JP5" gate="G$1" pin="2"/>
<wire x1="355.6" y1="254" x2="342.9" y2="254" width="0.1524" layer="91"/>
<label x="342.9" y="254" size="1.778" layer="95"/>
</segment>
</net>
<net name="URXD0" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA9"/>
<wire x1="218.44" y1="279.4" x2="218.44" y2="269.24" width="0.1524" layer="91"/>
<label x="218.44" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="JP5" gate="G$1" pin="1"/>
<wire x1="355.6" y1="256.54" x2="342.9" y2="256.54" width="0.1524" layer="91"/>
<label x="342.9" y="256.54" size="1.778" layer="95"/>
</segment>
</net>
<net name="1.8VSAM" class="0">
<segment>
<pinref part="C16" gate="G$1" pin="P$2"/>
<wire x1="88.9" y1="284.48" x2="101.6" y2="284.48" width="0.1524" layer="91"/>
<label x="93.98" y="284.48" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="VDDPLL"/>
<wire x1="185.42" y1="337.82" x2="185.42" y2="350.52" width="0.1524" layer="91"/>
<label x="185.42" y="340.36" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="C17" gate="G$1" pin="P$2"/>
<wire x1="45.72" y1="254" x2="50.8" y2="254" width="0.1524" layer="91"/>
<wire x1="50.8" y1="254" x2="50.8" y2="266.7" width="0.1524" layer="91"/>
<wire x1="50.8" y1="266.7" x2="63.5" y2="266.7" width="0.1524" layer="91"/>
<pinref part="C18" gate="G$1" pin="P$2"/>
<wire x1="50.8" y1="266.7" x2="45.72" y2="266.7" width="0.1524" layer="91"/>
<label x="53.34" y="266.7" size="1.778" layer="95"/>
<junction x="50.8" y="266.7"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="VDDOUT"/>
<wire x1="170.18" y1="309.88" x2="157.48" y2="309.88" width="0.1524" layer="91"/>
<label x="157.48" y="309.88" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="C14" gate="G$1" pin="P$2"/>
<wire x1="88.9" y1="325.12" x2="93.98" y2="325.12" width="0.1524" layer="91"/>
<wire x1="93.98" y1="325.12" x2="93.98" y2="337.82" width="0.1524" layer="91"/>
<wire x1="93.98" y1="337.82" x2="93.98" y2="350.52" width="0.1524" layer="91"/>
<wire x1="93.98" y1="350.52" x2="106.68" y2="350.52" width="0.1524" layer="91"/>
<pinref part="C11" gate="G$1" pin="P$2"/>
<wire x1="88.9" y1="350.52" x2="93.98" y2="350.52" width="0.1524" layer="91"/>
<junction x="93.98" y="350.52"/>
<pinref part="C13" gate="G$1" pin="P$2"/>
<wire x1="88.9" y1="337.82" x2="93.98" y2="337.82" width="0.1524" layer="91"/>
<junction x="93.98" y="337.82"/>
<label x="96.52" y="350.52" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="VDDCORE1"/>
<wire x1="170.18" y1="299.72" x2="157.48" y2="299.72" width="0.1524" layer="91"/>
<label x="157.48" y="299.72" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="VDDCORE2"/>
<wire x1="203.2" y1="279.4" x2="203.2" y2="266.7" width="0.1524" layer="91"/>
<label x="203.2" y="266.7" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="U4" gate="G$1" pin="VDDCORE3"/>
<wire x1="210.82" y1="337.82" x2="210.82" y2="350.52" width="0.1524" layer="91"/>
<label x="210.82" y="340.36" size="1.778" layer="95" rot="R90"/>
</segment>
</net>
<net name="TWCK0" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA4"/>
<wire x1="236.22" y1="297.18" x2="246.38" y2="297.18" width="0.1524" layer="91"/>
<label x="238.76" y="297.18" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="246.38" y1="187.96" x2="246.38" y2="203.2" width="0.1524" layer="91"/>
<wire x1="246.38" y1="203.2" x2="254" y2="203.2" width="0.1524" layer="91"/>
<wire x1="266.7" y1="203.2" x2="254" y2="203.2" width="0.1524" layer="91"/>
<wire x1="254" y1="203.2" x2="254" y2="213.36" width="0.1524" layer="91"/>
<pinref part="R7" gate="G$1" pin="P$1"/>
<wire x1="254" y1="213.36" x2="256.54" y2="213.36" width="0.1524" layer="91"/>
<label x="261.62" y="203.2" size="1.778" layer="95"/>
<pinref part="U$15" gate="G$1" pin="SCLK"/>
<junction x="254" y="203.2"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="2"/>
<wire x1="393.7" y1="284.48" x2="381" y2="284.48" width="0.1524" layer="91"/>
<label x="381" y="284.48" size="1.778" layer="95"/>
</segment>
</net>
<net name="TWD0" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA3"/>
<wire x1="236.22" y1="314.96" x2="246.38" y2="314.96" width="0.1524" layer="91"/>
<label x="238.76" y="314.96" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="248.92" y1="187.96" x2="248.92" y2="190.5" width="0.1524" layer="91"/>
<pinref part="R8" gate="G$1" pin="P$1"/>
<wire x1="248.92" y1="190.5" x2="254" y2="190.5" width="0.1524" layer="91"/>
<wire x1="254" y1="190.5" x2="256.54" y2="190.5" width="0.1524" layer="91"/>
<wire x1="254" y1="190.5" x2="254" y2="198.12" width="0.1524" layer="91"/>
<junction x="254" y="190.5"/>
<wire x1="254" y1="198.12" x2="266.7" y2="198.12" width="0.1524" layer="91"/>
<label x="261.62" y="198.12" size="1.778" layer="95"/>
<pinref part="U$15" gate="G$1" pin="SDATA"/>
</segment>
<segment>
<pinref part="JP6" gate="G$1" pin="1"/>
<wire x1="393.7" y1="287.02" x2="381" y2="287.02" width="0.1524" layer="91"/>
<label x="381" y="287.02" size="1.778" layer="95"/>
</segment>
</net>
<net name="URXD1" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PB2"/>
<wire x1="170.18" y1="317.5" x2="160.02" y2="317.5" width="0.1524" layer="91"/>
<label x="160.02" y="317.5" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="2_TXD1"/>
<wire x1="383.54" y1="157.48" x2="393.7" y2="157.48" width="0.1524" layer="91"/>
<label x="386.08" y="157.48" size="1.778" layer="95"/>
</segment>
</net>
<net name="UTXD1" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PB3"/>
<wire x1="170.18" y1="314.96" x2="160.02" y2="314.96" width="0.1524" layer="91"/>
<label x="160.02" y="314.96" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="3_RXD1"/>
<wire x1="383.54" y1="162.56" x2="393.7" y2="162.56" width="0.1524" layer="91"/>
<label x="386.08" y="162.56" size="1.778" layer="95"/>
</segment>
</net>
<net name="MISO" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA12"/>
<wire x1="210.82" y1="279.4" x2="210.82" y2="269.24" width="0.1524" layer="91"/>
<label x="210.82" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<wire x1="187.96" y1="60.96" x2="200.66" y2="60.96" width="0.1524" layer="91"/>
<label x="195.58" y="60.96" size="1.778" layer="95"/>
<pinref part="U$1" gate="G$1" pin="SDO"/>
</segment>
</net>
<net name="MOSI" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA13"/>
<wire x1="198.12" y1="279.4" x2="198.12" y2="269.24" width="0.1524" layer="91"/>
<label x="198.12" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<wire x1="187.96" y1="66.04" x2="200.66" y2="66.04" width="0.1524" layer="91"/>
<label x="195.58" y="66.04" size="1.778" layer="95"/>
<pinref part="U$1" gate="G$1" pin="SDI"/>
</segment>
</net>
<net name="SPCK" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA14"/>
<wire x1="195.58" y1="279.4" x2="195.58" y2="269.24" width="0.1524" layer="91"/>
<label x="195.58" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<wire x1="187.96" y1="55.88" x2="200.66" y2="55.88" width="0.1524" layer="91"/>
<label x="195.58" y="55.88" size="1.778" layer="95"/>
<pinref part="U$1" gate="G$1" pin="SCLK"/>
</segment>
</net>
<net name="NPCS0" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA11"/>
<wire x1="213.36" y1="279.4" x2="213.36" y2="269.24" width="0.1524" layer="91"/>
<label x="213.36" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<wire x1="187.96" y1="71.12" x2="200.66" y2="71.12" width="0.1524" layer="91"/>
<label x="195.58" y="71.12" size="1.778" layer="95"/>
<pinref part="U$1" gate="G$1" pin="NSEL"/>
</segment>
</net>
<net name="TCXOEN" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA8"/>
<wire x1="220.98" y1="279.4" x2="220.98" y2="269.24" width="0.1524" layer="91"/>
<label x="220.98" y="269.24" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="TCXO" gate="G$1" pin="VDD"/>
<wire x1="132.08" y1="111.76" x2="121.92" y2="111.76" width="0.1524" layer="91"/>
<pinref part="CD5" gate="G$1" pin="P$2"/>
<wire x1="121.92" y1="111.76" x2="106.68" y2="111.76" width="0.1524" layer="91"/>
<wire x1="121.92" y1="109.22" x2="121.92" y2="111.76" width="0.1524" layer="91"/>
<junction x="121.92" y="111.76"/>
<label x="106.68" y="111.76" size="1.778" layer="95"/>
</segment>
</net>
<net name="AD3" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA20"/>
<wire x1="170.18" y1="289.56" x2="160.02" y2="289.56" width="0.1524" layer="91"/>
<label x="160.02" y="289.56" size="1.778" layer="95"/>
</segment>
<segment>
<pinref part="R9" gate="G$1" pin="P$2"/>
<wire x1="66.04" y1="172.72" x2="73.66" y2="172.72" width="0.1524" layer="91"/>
<label x="68.58" y="172.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="AD9" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA22"/>
<wire x1="170.18" y1="294.64" x2="160.02" y2="294.64" width="0.1524" layer="91"/>
<label x="160.02" y="294.64" size="1.778" layer="95"/>
</segment>
<segment>
<wire x1="53.34" y1="152.4" x2="50.8" y2="152.4" width="0.1524" layer="91"/>
<wire x1="50.8" y1="152.4" x2="48.26" y2="152.4" width="0.1524" layer="91"/>
<wire x1="50.8" y1="152.4" x2="50.8" y2="160.02" width="0.1524" layer="91"/>
<junction x="50.8" y="152.4"/>
<label x="53.34" y="160.02" size="1.778" layer="95"/>
<wire x1="50.8" y1="160.02" x2="58.42" y2="160.02" width="0.1524" layer="91"/>
<pinref part="R14" gate="G$1" pin="P$2"/>
<pinref part="R15" gate="G$1" pin="P$1"/>
</segment>
</net>
<net name="PA5" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA5"/>
<wire x1="236.22" y1="294.64" x2="246.38" y2="294.64" width="0.1524" layer="91"/>
<label x="238.76" y="294.64" size="1.778" layer="95"/>
</segment>
</net>
<net name="PA6" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA6"/>
<wire x1="236.22" y1="292.1" x2="246.38" y2="292.1" width="0.1524" layer="91"/>
<label x="238.76" y="292.1" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$19" class="0">
<segment>
<pinref part="U$10" gate="G$1" pin="D+"/>
<wire x1="373.38" y1="330.2" x2="360.68" y2="330.2" width="0.1524" layer="91"/>
<wire x1="360.68" y1="330.2" x2="360.68" y2="322.58" width="0.1524" layer="91"/>
<pinref part="R11" gate="G$1" pin="P$2"/>
<wire x1="360.68" y1="322.58" x2="358.14" y2="322.58" width="0.1524" layer="91"/>
</segment>
</net>
<net name="N$20" class="0">
<segment>
<pinref part="U$10" gate="G$1" pin="D-"/>
<wire x1="373.38" y1="332.74" x2="360.68" y2="332.74" width="0.1524" layer="91"/>
<wire x1="360.68" y1="332.74" x2="360.68" y2="335.28" width="0.1524" layer="91"/>
<pinref part="R10" gate="G$1" pin="P$2"/>
<wire x1="360.68" y1="335.28" x2="358.14" y2="335.28" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VBUS" class="0">
<segment>
<pinref part="U$9" gate="G$1" pin="VIN"/>
<wire x1="353.06" y1="370.84" x2="358.14" y2="370.84" width="0.1524" layer="91"/>
<pinref part="C26" gate="G$1" pin="P$2"/>
<wire x1="358.14" y1="370.84" x2="368.3" y2="370.84" width="0.1524" layer="91"/>
<wire x1="358.14" y1="365.76" x2="358.14" y2="370.84" width="0.1524" layer="91"/>
<junction x="358.14" y="370.84"/>
<pinref part="U$10" gate="G$1" pin="VBUS"/>
<wire x1="373.38" y1="335.28" x2="368.3" y2="335.28" width="0.1524" layer="91"/>
<wire x1="368.3" y1="335.28" x2="368.3" y2="370.84" width="0.1524" layer="91"/>
</segment>
<segment>
<wire x1="393.7" y1="269.24" x2="381" y2="269.24" width="0.1524" layer="91"/>
<label x="381" y="269.24" size="1.778" layer="95"/>
<pinref part="JP7" gate="G$1" pin="1"/>
</segment>
</net>
<net name="PA1" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PA1"/>
<wire x1="236.22" y1="325.12" x2="246.38" y2="325.12" width="0.1524" layer="91"/>
<label x="238.76" y="325.12" size="1.778" layer="95"/>
</segment>
</net>
<net name="DDP" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PB11"/>
<wire x1="203.2" y1="337.82" x2="203.2" y2="347.98" width="0.1524" layer="91"/>
<label x="203.2" y="342.9" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="R11" gate="G$1" pin="P$1"/>
<wire x1="342.9" y1="322.58" x2="332.74" y2="322.58" width="0.1524" layer="91"/>
<label x="332.74" y="322.58" size="1.778" layer="95"/>
</segment>
</net>
<net name="DDM" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PB10"/>
<wire x1="205.74" y1="337.82" x2="205.74" y2="347.98" width="0.1524" layer="91"/>
<label x="205.74" y="342.9" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="R10" gate="G$1" pin="P$1"/>
<wire x1="342.9" y1="335.28" x2="332.74" y2="335.28" width="0.1524" layer="91"/>
<label x="332.74" y="335.28" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="CH" gate="G$1" pin="P$2"/>
<wire x1="114.3" y1="48.26" x2="114.3" y2="40.64" width="0.1524" layer="91"/>
<wire x1="114.3" y1="48.26" x2="109.22" y2="48.26" width="0.1524" layer="91"/>
<pinref part="LH" gate="G$1" pin="P$2"/>
<wire x1="109.22" y1="48.26" x2="104.14" y2="48.26" width="0.1524" layer="91"/>
<wire x1="104.14" y1="48.26" x2="104.14" y2="43.18" width="0.1524" layer="91"/>
<pinref part="C0" gate="G$1" pin="P$1"/>
<pinref part="L0" gate="G$1" pin="P$2"/>
<wire x1="106.68" y1="53.34" x2="109.22" y2="53.34" width="0.1524" layer="91"/>
<wire x1="109.22" y1="53.34" x2="116.84" y2="53.34" width="0.1524" layer="91"/>
<wire x1="109.22" y1="48.26" x2="109.22" y2="53.34" width="0.1524" layer="91"/>
<junction x="109.22" y="48.26"/>
<junction x="109.22" y="53.34"/>
</segment>
</net>
<net name="N$1" class="0">
<segment>
<pinref part="LH" gate="G$1" pin="P$1"/>
<wire x1="104.14" y1="25.4" x2="104.14" y2="27.94" width="0.1524" layer="91"/>
<pinref part="CH" gate="G$1" pin="P$1"/>
<wire x1="114.3" y1="30.48" x2="114.3" y2="25.4" width="0.1524" layer="91"/>
<wire x1="104.14" y1="25.4" x2="109.22" y2="25.4" width="0.1524" layer="91"/>
<wire x1="109.22" y1="25.4" x2="114.3" y2="25.4" width="0.1524" layer="91"/>
<wire x1="109.22" y1="25.4" x2="109.22" y2="15.24" width="0.1524" layer="91"/>
<junction x="109.22" y="25.4"/>
<pinref part="RH" gate="G$1" pin="P$2"/>
<wire x1="109.22" y1="15.24" x2="104.14" y2="15.24" width="0.1524" layer="91"/>
</segment>
</net>
<net name="POWER_IN" class="0">
<segment>
<wire x1="365.76" y1="48.26" x2="363.22" y2="48.26" width="0.1524" layer="91"/>
<wire x1="363.22" y1="48.26" x2="363.22" y2="33.02" width="0.1524" layer="91"/>
<wire x1="363.22" y1="33.02" x2="363.22" y2="30.48" width="0.1524" layer="91"/>
<wire x1="363.22" y1="30.48" x2="345.44" y2="30.48" width="0.1524" layer="91"/>
<pinref part="C1" gate="G$1" pin="P$2"/>
<wire x1="363.22" y1="33.02" x2="365.76" y2="33.02" width="0.1524" layer="91"/>
<junction x="363.22" y="33.02"/>
<label x="345.44" y="30.48" size="1.778" layer="95"/>
<wire x1="391.16" y1="48.26" x2="396.24" y2="48.26" width="0.1524" layer="91"/>
<wire x1="396.24" y1="48.26" x2="396.24" y2="20.32" width="0.1524" layer="91"/>
<wire x1="396.24" y1="20.32" x2="363.22" y2="20.32" width="0.1524" layer="91"/>
<wire x1="363.22" y1="20.32" x2="363.22" y2="30.48" width="0.1524" layer="91"/>
<junction x="363.22" y="30.48"/>
<wire x1="391.16" y1="53.34" x2="396.24" y2="53.34" width="0.1524" layer="91"/>
<wire x1="396.24" y1="53.34" x2="396.24" y2="48.26" width="0.1524" layer="91"/>
<junction x="396.24" y="48.26"/>
<pinref part="U3" gate="G$1" pin="VIN"/>
<pinref part="U3" gate="G$1" pin="VINA"/>
<pinref part="U3" gate="G$1" pin="EN"/>
</segment>
<segment>
<wire x1="33.02" y1="152.4" x2="15.24" y2="152.4" width="0.1524" layer="91"/>
<label x="15.24" y="152.4" size="1.778" layer="95"/>
<pinref part="R14" gate="G$1" pin="P$1"/>
</segment>
</net>
<net name="TIMEPULSE" class="0">
<segment>
<pinref part="U4" gate="G$1" pin="PB6"/>
<wire x1="218.44" y1="337.82" x2="218.44" y2="347.98" width="0.1524" layer="91"/>
<label x="218.44" y="340.36" size="1.778" layer="95" rot="R90"/>
</segment>
<segment>
<pinref part="U$2" gate="G$1" pin="4_TIMEPULSE"/>
<wire x1="383.54" y1="167.64" x2="393.7" y2="167.64" width="0.1524" layer="91"/>
<label x="386.08" y="167.64" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
