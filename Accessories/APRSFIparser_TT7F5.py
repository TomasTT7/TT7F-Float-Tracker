# Parsing APRS.fi data
# raw packets: 2017-07-20 20:39:51 CEST: OK7DMT-7>APRS,WIDE2-1,qAR,OK0DSK-1,T2CZECH:!/5L+"S);UOJRW 1G41<5MH:S(L[HF-/;v+:14!'|!,!*<e*w0h!'!$|
# input file: APRSfi_TT7F5.txt
# Output KML and CSV

import numpy as np

OFFSETtempmcu = 3.0
GMToffset = 2          # CEST +2

callsign = []
packet = []
year = []
month = []
day = []
hour = []
minute = []
second = []
latitude = []
longitude = []
altitude = []
sequence = []
vsolar = []
vbattery = []
tempmcu = []
temptx = []
satellite = []
bitfield = []
bit0 = []
bit1 = []
bit2 = []
bit3 = []
bit4 = []
bit5 = []
bit6 = []
bit7 = []
backlog = []

GMT = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23]
MONTHSn = [0,31,28,31,30,31,30,31,31,30,31,30,31]
MONTHSnL = [0,31,29,31,30,31,30,31,31,30,31,30,31]

f = open('APRSfi_TT7F5.txt', 'r')
rawdata = f.read()
f.close

splitlines = rawdata.split('\n')

for i in range(len(splitlines)):
    
    splitcolon = splitlines[i].split(':', 4)
    packet = splitcolon[4]

    if packet[15] == '|':   # packet without backlog

        # current data
        if (int(splitcolon[0][11:13]) - GMToffset) < 0:
            
            h = GMT[int(splitcolon[0][11:13]) - GMToffset]

            if int(splitcolon[0][8:10]) == 1:    # day of month
                
                if (int(splitcolon[0][0:4]) % 4) == 0:    # leap year

                    if int(splitcolon[0][5:7]) == 1:    # month

                        d = 31
                        m = 12
                        y = int(splitcolon[0][0:4]) - 1

                    else:

                        d = MONTHSnL[int(splitcolon[0][5:7]) - 1]
                        m = int(splitcolon[0][5:7]) - 1
                        y = int(splitcolon[0][0:4])

                else:

                    if int(splitcolon[0][5:7]) == 1:    # month

                        d = 31
                        m = 12
                        y = int(splitcolon[0][0:4]) - 1

                    else:

                        d = MONTHSn[int(splitcolon[0][5:7]) - 1]
                        m = int(splitcolon[0][5:7]) - 1
                        y = int(splitcolon[0][0:4])

            else:

                d = int(splitcolon[0][8:10]) - 1
                m = int(splitcolon[0][5:7])
                y = int(splitcolon[0][0:4])                

        else:

            h = int(splitcolon[0][11:13]) - GMToffset
            d = int(splitcolon[0][8:10])
            m = int(splitcolon[0][5:7])
            y = int(splitcolon[0][0:4])
        
        callsign.append(splitcolon[3][1:10])
        year.append(y)
        month.append(m)
        day.append(d)
        hour.append(h)
        minute.append(int(splitcolon[1]))
        second.append(int(splitcolon[2][0:2]))
        latitude.append(90 - ((ord(packet[2]) - 33) * 91**3 + (ord(packet[3]) - 33) * 91**2 + (ord(packet[4]) - 33) * 91 + (ord(packet[5]) - 33)) / 380926.0)
        longitude.append(-180 + ((ord(packet[6]) - 33) * 91**3 + (ord(packet[7]) - 33) * 91**2 + (ord(packet[8]) - 33) * 91 + (ord(packet[9]) - 33)) / 190463.0)
        altitude.append(1.002**((ord(packet[11]) - 33) * 91 + ord(packet[12]) - 33) * 0.3048)
        sequence.append(((ord(packet[16]) - 33) * 91 + (ord(packet[17]) - 33)))
        vsolar.append(((ord(packet[18]) - 33) * 91 + (ord(packet[19]) - 33)) * 0.0008)
        vbattery.append(((ord(packet[20]) - 33) * 91 + (ord(packet[21]) - 33)) * 0.0016)
        tempmcu.append(((ord(packet[22]) - 33) * 91 + (ord(packet[23]) - 33)) * 0.304 - 273.15 + OFFSETtempmcu)
        temptx.append(((ord(packet[24]) - 33) * 91 + (ord(packet[25]) - 33)) * 0.222 - 297.0)
        satellite.append((ord(packet[26]) - 33) * 91 + (ord(packet[27]) - 33))
        bitfield.append((ord(packet[29]) - 33))
        bit0.append((ord(packet[29]) - 33) & 0b00000001)
        bit1.append(((ord(packet[29]) - 33) & 0b00000010) >> 1)
        bit2.append(((ord(packet[29]) - 33) & 0b00000100) >> 2)
        bit3.append(((ord(packet[29]) - 33) & 0b00001000) >> 3)
        bit4.append(((ord(packet[29]) - 33) & 0b00010000) >> 4)
        bit5.append(((ord(packet[29]) - 33) & 0b00100000) >> 5)
        bit6.append(((ord(packet[29]) - 33) & 0b01000000) >> 6)
        bit7.append(((ord(packet[29]) - 33) & 0b10000000) >> 7)
        backlog.append("No")
        
    else:                   # packet with backlog

        # current data
        if (int(splitcolon[0][11:13]) - GMToffset) < 0:
            
            h = GMT[int(splitcolon[0][11:13]) - GMToffset]

            if int(splitcolon[0][8:10]) == 1:    # day of month
                
                if (int(splitcolon[0][0:4]) % 4) == 0:    # leap year

                    if int(splitcolon[0][5:7]) == 1:    # month

                        d = 31
                        m = 12
                        y = int(splitcolon[0][0:4]) - 1

                    else:

                        d = MONTHSnL[int(splitcolon[0][5:7]) - 1]
                        m = int(splitcolon[0][5:7]) - 1
                        y = int(splitcolon[0][0:4])

                else:

                    if int(splitcolon[0][5:7]) == 1:    # month

                        d = 31
                        m = 12
                        y = int(splitcolon[0][0:4]) - 1

                    else:

                        d = MONTHSn[int(splitcolon[0][5:7]) - 1]
                        m = int(splitcolon[0][5:7]) - 1
                        y = int(splitcolon[0][0:4])

            else:

                d = int(splitcolon[0][8:10]) - 1
                m = int(splitcolon[0][5:7])
                y = int(splitcolon[0][0:4])                

        else:

            h = int(splitcolon[0][11:13]) - GMToffset
            d = int(splitcolon[0][8:10])
            m = int(splitcolon[0][5:7])
            y = int(splitcolon[0][0:4])
        
        callsign.append(splitcolon[3][1:10])
        year.append(y)
        month.append(m)
        day.append(d)
        hour.append(h)
        minute.append(int(splitcolon[1]))
        second.append(int(splitcolon[2][0:2]))
        latitude.append(90 - ((ord(packet[2]) - 33) * 91**3 + (ord(packet[3]) - 33) * 91**2 + (ord(packet[4]) - 33) * 91 + (ord(packet[5]) - 33)) / 380926.0)
        longitude.append(-180 + ((ord(packet[6]) - 33) * 91**3 + (ord(packet[7]) - 33) * 91**2 + (ord(packet[8]) - 33) * 91 + (ord(packet[9]) - 33)) / 190463.0)
        altitude.append(1.002**((ord(packet[11]) - 33) * 91 + ord(packet[12]) - 33) * 0.3048)
        sequence.append(((ord(packet[41]) - 33) * 91 + (ord(packet[42]) - 33)))
        vsolar.append(((ord(packet[43]) - 33) * 91 + (ord(packet[44]) - 33)) * 0.0008)
        vbattery.append(((ord(packet[45]) - 33) * 91 + (ord(packet[46]) - 33)) * 0.0016)
        tempmcu.append(((ord(packet[47]) - 33) * 91 + (ord(packet[48]) - 33)) * 0.304 - 273.15 + OFFSETtempmcu)
        temptx.append(((ord(packet[49]) - 33) * 91 + (ord(packet[50]) - 33)) * 0.222 - 297.0)
        satellite.append((ord(packet[51]) - 33) * 91 + (ord(packet[52]) - 33))
        bitfield.append((ord(packet[54]) - 33))
        bit0.append((ord(packet[54]) - 33) & 0b00000001)
        bit1.append(((ord(packet[54]) - 33) & 0b00000010) >> 1)
        bit2.append(((ord(packet[54]) - 33) & 0b00000100) >> 2)
        bit3.append(((ord(packet[54]) - 33) & 0b00001000) >> 3)
        bit4.append(((ord(packet[54]) - 33) & 0b00010000) >> 4)
        bit5.append(((ord(packet[54]) - 33) & 0b00100000) >> 5)
        bit6.append(((ord(packet[54]) - 33) & 0b01000000) >> 6)
        bit7.append(((ord(packet[54]) - 33) & 0b10000000) >> 7)
        backlog.append("No")
        
        # backlog
        callsign.append(splitcolon[3][1:10])
        year.append(2016 + ord(packet[15]) - 48)
        month.append(ord(packet[16]) - 64)
        day.append(ord(packet[17]) - 33)
        hour.append(ord(packet[18]) - 33)
        minute.append(ord(packet[19]) - 33)
        second.append(0)
        latitude.append(90 - ((ord(packet[20]) - 33) * 91**3 + (ord(packet[21]) - 33) * 91**2 + (ord(packet[22]) - 33) * 91 + (ord(packet[23]) - 33)) / 380926.0)
        longitude.append(-180 + ((ord(packet[24]) - 33) * 91**3 + (ord(packet[25]) - 33) * 91**2 + (ord(packet[26]) - 33) * 91 + (ord(packet[27]) - 33)) / 190463.0)
        altitude.append(1.002**((ord(packet[28]) - 33) * 91 + ord(packet[29]) - 33) * 0.3048)
        sequence.append(0)
        vsolar.append(((ord(packet[30]) - 33) * 91 + (ord(packet[31]) - 33)) * 0.0008)
        vbattery.append(((ord(packet[32]) - 33) * 91 + (ord(packet[33]) - 33)) * 0.0016)
        tempmcu.append(((ord(packet[34]) - 33) * 91 + (ord(packet[35]) - 33)) * 0.304 - 273.15 + OFFSETtempmcu)
        temptx.append(((ord(packet[36]) - 33) * 91 + (ord(packet[37]) - 33)) * 0.222 - 297.0)
        satellite.append((ord(packet[38]) - 33) * 91 + (ord(packet[39]) - 33))
        bitfield.append(0)
        bit0.append(0)
        bit1.append(0)
        bit2.append(0)
        bit3.append(0)
        bit4.append(0)
        bit5.append(0)
        bit6.append(0)
        bit7.append(0)
        backlog.append("Yes")
    

# Data
dataOUT = []
dataORDERED = []

for i in range(len(year)):

    #print ('{:s} {:d} {:02d} {:02d} {:02d} {:02d} {:02d} {:.5f} {:.5f} {:.0f} {:d} {:.3f} {:.3f} {:.1f} {:.1f} {:d} {:d} {:d} {:d} {:d} {:08b} {:s}' \
    #      .format(callsign[i], year[i], month[i], day[i], hour[i], minute[i], second[i], latitude[i], longitude[i], altitude[i], sequence[i], vsolar[i], vbattery[i], tempmcu[i], temptx[i], satellite[i], bit0[i], bit1[i], bit2[i], bit3[i], bitfield[i], backlog[i]))
    dataOUT.append(('{:s} {:d} {:02d} {:02d} {:02d} {:02d} {:02d} {:.5f} {:.5f} {:.0f} {:d} {:.3f} {:.3f} {:.1f} {:.1f} {:d} {:d} {:d} {:d} {:d} {:08b} {:s}' \
          .format(callsign[i], year[i], month[i], day[i], hour[i], minute[i], second[i], latitude[i], longitude[i], altitude[i], sequence[i], vsolar[i], vbattery[i], tempmcu[i], temptx[i], satellite[i], bit0[i], bit1[i], bit2[i], bit3[i], bitfield[i], backlog[i])))

#print('\n')
dataOUT.sort()

for i in range(len(dataOUT)):

    if len(dataOUT) == 1:
        
        dataORDERED.append(dataOUT[i])
        print dataOUT[i]
    
    if dataOUT[i] != dataOUT[i-1]:
        
        dataORDERED.append(dataOUT[i])
        print dataOUT[i]

#print('\n')

# CSV
f1= open('TT7F5data.csv', 'w')
f1.write("""Timestamp,Solar,Supercap,MCU,TX,Satellites,Sequence,Img,PSM\n""")

for i in range(len(dataORDERED)):
    
    dT = dataORDERED[i].split(' ')
    f1.write("""{:s}-{:s}-{:s} {:s}:{:s}:{:s},{:s},{:s},{:s},{:s},{:s},{:s},{:s},{:s}\n""".format(dT[1], dT[2], dT[3], dT[4], dT[5], dT[6], dT[11], dT[12], dT[13], dT[14], dT[15], dT[10], dT[18], dT[19]))

f1.close()


# KML
f = open('TT7F5data.kml', 'w')

f.write("""<?xml version="1.0" encoding="UTF-8"?>\n""")
f.write("""<kml xmlns="http://earth.google.com/kml/2.0">\n""")
f.write("""<Document>\n""")
f.write("""   <name>{:s}</name>\n""".format(callsign[0]))
f.write("""   <description>The flight path of TT7F5 superpressure balloon.</description>\n""")
f.write("""   <Style id="styleL">\n""")
f.write("""       <LineStyle>\n""")
f.write("""           <color>FF000000</color>\n""")
f.write("""           <width>2</width>\n""")
f.write("""       </LineStyle>\n""")
f.write("""       <PolyStyle>\n""")
f.write("""           <color>32000000</color>\n""")
f.write("""       </PolyStyle>\n""")
f.write("""   </Style>\n""")
f.write("""   <Style id="style">\n""")
f.write("""       <IconStyle>\n""")
f.write("""           <scale>0.25</scale>\n""")
f.write("""           <Icon>\n""")
f.write("""               <href>http://maps.google.com/mapfiles/dir_walk_0.png</href>\n""")
f.write("""           </Icon>\n""")
f.write("""       </IconStyle>\n""")
f.write("""       <BalloonStyle>\n""")
f.write("""           <text>\n""")
f.write("""               <![CDATA[
                    <B>Date:</B> $[Date]<br/>
                    <B>Time:</B> $[Time]<br/>
                    <B>Latitude:</B> $[Latitude]<br/>
                    <B>Longitude:</B> $[Longitude]<br/>
                    <B>Altitude:</B> $[Altitude]<br/>
                    <P>
                    <B>Sequence:</B> $[Sequence]<br/>
                    <B>Vsolar:</B> $[Solar Voltage]<br/>
                    <B>Vbattery:</B> $[Battery Voltage]<br/>
                    <B>Temperature MCU:</B> $[Temperature MCU]<br/>
                    <B>Temperature TX:</B> $[Temperature TX]<br/>
                    <B>Satellites:</B> $[Satellites]<br/>
                    <B>Image:</B> $[Image]<br/>
                    <B>Power Save Mode:</B> $[Power Save Mode]<br/>
                    <B>Backlogged:</B> $[Backlogged]<br/>
                ]]>\n""")
f.write("""           </text>\n""")
f.write("""       </BalloonStyle>\n""")
f.write("""   </Style>\n""")
f.write("""   <Folder>\n""")
f.write("""       <name>Flight Path</name>\n""")
f.write("""       <Placemark>\n""")
f.write("""           <name>Flight Path</name>\n""")
f.write("""           <styleUrl>#styleL</styleUrl>\n""")
f.write("""           <LineString>\n""")
f.write("""               <extrude>1</extrude>\n""")
f.write("""               <tessellate>1</tessellate>\n""")
f.write("""               <altitudeMode>absolute</altitudeMode>\n""")
f.write("""               <coordinates>\n""")

for i in range(len(dataORDERED)):
    
    dataTemp = dataORDERED[i].split(' ')
    f.write("""                 {:s},{:s},{:s}\n""".format(dataTemp[8], dataTemp[7], dataTemp[9]))

f.write("""               </coordinates>\n""")
f.write("""           </LineString>\n""")
f.write("""       </Placemark>\n""")
f.write("""   </Folder>\n""")
f.write("""   <Folder>\n""")
f.write("""       <name>Data Points</name>\n""")

for i in range(len(dataORDERED)):
    
    dTemp = dataORDERED[i].split(' ')
    f.write("""       <Placemark>\n""")
    f.write("""           <description>{:s}</description>\n""".format(callsign[0]))
    f.write("""           <styleUrl>#style</styleUrl>\n""")
    f.write("""           <ExtendedData>\n""")
    f.write("""               <Data name="Date"><value>{:s}/{:s}/{:s}</value></Data>\n""".format(dTemp[1], dTemp[2], dTemp[3]))
    f.write("""               <Data name="Time"><value>{:s}:{:s}:{:s}</value></Data>\n""".format(dTemp[4], dTemp[5], dTemp[6]))
    f.write("""               <Data name="Latitude"><value>{:s}</value></Data>\n""".format(dTemp[7]))
    f.write("""               <Data name="Longitude"><value>{:s}</value></Data>\n""".format(dTemp[8]))
    f.write("""               <Data name="Altitude"><value>{:s}</value></Data>\n""".format(dTemp[9]))
    f.write("""               <Data name="Sequence"><value>{:s}</value></Data>\n""".format(dTemp[10]))
    f.write("""               <Data name="Solar Voltage"><value>{:s}</value></Data>\n""".format(dTemp[11]))
    f.write("""               <Data name="Battery Voltage"><value>{:s}</value></Data>\n""".format(dTemp[12]))
    f.write("""               <Data name="Temperature MCU"><value>{:s}</value></Data>\n""".format(dTemp[13]))
    f.write("""               <Data name="Temperature TX"><value>{:s}</value></Data>\n""".format(dTemp[14]))
    f.write("""               <Data name="Satellites"><value>{:s}</value></Data>\n""".format(dTemp[15]))
    f.write("""               <Data name="Image"><value>{:s}</value></Data>\n""".format(dTemp[18]))
    f.write("""               <Data name="Power Save Mode"><value>{:s}</value></Data>\n""".format(dTemp[19]))
    f.write("""               <Data name="Backlogged"><value>{:s}</value></Data>\n""".format(dTemp[21]))
    f.write("""           </ExtendedData>\n""")
    f.write("""           <Point>\n""")
    f.write("""               <coordinates>\n""")
    f.write("""                   {:s},{:s},{:s}\n""".format(dTemp[8], dTemp[7], dTemp[9]))
    f.write("""               </coordinates>\n""")
    f.write("""           </Point>\n""")
    f.write("""       </Placemark>\n""")

f.write("""   </Folder>\n""")
f.write("""</Document>\n""")
f.write("""</kml>\n""")

f.close()
print "Done."
