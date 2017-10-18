# WSPRNET.ORG data to KML


def locatorToGPS(loc):

    lon = -180.0 + (ord(loc[0]) - 65.0) * 20.0
    lat = -90.0 + (ord(loc[1]) - 65.0) * 10.0

    if len(loc) == 4:
        lon += (ord(loc[2]) - 48.0 + 0.5) * 2.0
        lat += (ord(loc[3]) - 48.0 + 0.5) * 1.0
    else:
        lon += (ord(loc[2]) - 48.0) * 2.0
        lat += (ord(loc[3]) - 48.0) * 1.0

        lon += (ord(loc[4]) - 97.0 + 0.5) * 0.0834
        lat += (ord(loc[5]) - 97.0 + 0.5) * 0.0417

    return lat, lon


year = []
month = []
day = []
hour = []
minute = []
callsign = []
frequency = []
snr = []
drift = []
locator = []
power = []
receiver = []
locatorR = []
distance = []
latitude = []
longitude = []
alt = []
altitude = []
latitudeR = []
longitudeR = []

powerDict = {'0': 0, '3': 1000, '7': 2000, '10': 3000, '13': 4000, '17': 5000,
             '20': 6000, '23': 7000, '27': 8000, '30': 9000, '33': 10000, '37': 11000,
             '40': 12000, '43': 13000, '47': 14000, '50': 15000, '53': 16000, '57': 17000,
             '60': 18000}

powerDictF = {'0': 0, '3': 53, '7': 106, '10': 159, '13': 212, '17': 265,
             '20': 318, '23': 371, '27': 424, '30': 477, '33': 530, '37': 583,
             '40': 636, '43': 689, '47': 742, '50': 795, '53': 848, '57': 901,
             '60': 954}

f = open('WSPRNETorg_TT7F6W-all.txt', 'r')
rawdata = f.read()
f.close

splitlines = rawdata.split('\n')

for i in reversed(range(len(splitlines))):

    removespace = splitlines[i].replace(" ", "")
    splittab = removespace.split('\t')

    year.append(splittab[0][0:4])
    month.append(splittab[0][5:7])
    day.append(splittab[0][8:10])
    hour.append(splittab[0][10:12])
    minute.append(splittab[0][13:15])
    callsign.append(splittab[1])
    frequency.append(splittab[2])
    snr.append(splittab[3])
    drift.append(splittab[4])
    locator.append(splittab[5])
    power.append(splittab[6])
    receiver.append(splittab[8])
    locatorR.append(splittab[9])
    distance.append(splittab[10])


# Locator and Altitude
for i in range(len(year)):

    if minute[i][1] == '4':
        alt.append(powerDict[power[i][1:]])
    else:
        alt.append(powerDictF[power[i][1:]])


for i in range(len(year)):

    if minute[i][1] == '4':

        tsNow1 = year[i] + month[i] + day[i] + hour[i] + minute[i][0] + '6'
        
        for y in range(len(year)):

            tsHist1 = year[y] + month[y] + day[y] + hour[y] + minute[y]
            
            if tsNow1 == tsHist1:
                locator[i] = locator[y]
                altitude.append(alt[i] + alt[y])
                break

            if y == len(year) - 1:
                locator[i] = locator[i][:4]
                altitude.append(alt[i])

    elif minute[i][1] == '6':

        tsNow2 = year[i] + month[i] + day[i] + hour[i] + minute[i][0] + '4'

        for z in range(len(year)):

            tsHist2 = year[z] + month[z] + day[z] + hour[z] + minute[z]

            if tsNow2 == tsHist2:
                altitude.append(alt[i] + alt[z])
                break

            if z == len(year) - 1:
                altitude.append(alt[i])


for i in range(len(year)):
    
    latit, longit = locatorToGPS(locator[i])

    latitude.append(latit)
    longitude.append(longit)

    latit, longit = locatorToGPS(locatorR[i])

    latitudeR.append(latit)
    longitudeR.append(longit)


# KML
f = open('TT7F6WdataW_receivers.kml', 'w')

f.write("""<?xml version="1.0" encoding="UTF-8"?>
<kml xmlns="http://earth.google.com/kml/2.0">
<Document>
<name>{:s}</name>
   <description>The flight path of TT7F6W superpressure balloon.</description>
   <Style id="styleL">
       <LineStyle>
           <color>641400FF</color>
           <width>2</width>
       </LineStyle>
       <PolyStyle>
           <color>321400FF</color>
       </PolyStyle>
   </Style>
   <Style id="style">
       <IconStyle>
           <scale>1.0</scale>
           <Icon>
               <href>http://maps.google.com/mapfiles/kml/shapes/placemark_circle_highlight.png</href>
           </Icon>
       </IconStyle>
       <LabelStyle>
           <scale>0</scale>
       </LabelStyle>
       <BalloonStyle>
           <text>
               <![CDATA[
                    <B>Date:</B> $[Date]<br/>
                    <B>Time:</B> $[Time]<br/>
                    <B>Latitude:</B> $[Latitude]<br/>
                    <B>Longitude:</B> $[Longitude]<br/>
                    <B>Altitude:</B> $[Altitude]<br/>
                    <B>Locator:</B> $[Locator]<br/>
                ]]>
           </text>
       </BalloonStyle>
   </Style>
   <Style id="styleR">
       <IconStyle>
           <scale>1.5</scale>
           <Icon>
               <href>http://maps.google.com/mapfiles/kml/paddle/ltblu-diamond.png</href>
           </Icon>
       </IconStyle>
       <LabelStyle>
           <scale>0</scale>
       </LabelStyle>
       <BalloonStyle>
           <text>
               <![CDATA[
                    <B>Receiver:</B> $[Receiver]<br/>
                    <B>Latitude:</B> $[Latitude]<br/>
                    <B>Longitude:</B> $[Longitude]<br/>
                    <B>Locator:</B> $[Locator]<br/>
                    <B>Distance:</B> $[Distance]<br/>
                    <B>Frequency:</B> $[Frequency]<br/>
                    <B>SNR:</B> $[SNR]<br/>
                    <B>Drift:</B> $[Drift]<br/>
                ]]>
           </text>
       </BalloonStyle>
   </Style>
   <Folder>
       <name>Flight Path WSPR</name>
       <Placemark>
           <name>Flight Path</name>
           <styleUrl>#styleL</styleUrl>
           <LineString>
               <extrude>1</extrude>
               <tessellate>1</tessellate>
               <altitudeMode>absolute</altitudeMode>
               <coordinates>""".format(callsign[0]))

for i in range(len(year)):

    if i == 0:
        f.write("""                   {:s},{:s},{:s}\n""".format(str(longitude[i]), str(latitude[i]), str(altitude[i])))
        continue
    
    if year[i-1] == year[i] and month[i-1] == month[i] and day[i-1] == day[i] and hour[i-1] == hour[i] and minute[i-1] == minute[i]:
        continue
    else:
        f.write("""                   {:s},{:s},{:s}\n""".format(str(longitude[i]), str(latitude[i]), str(altitude[i])))

f.write("""               </coordinates>
           </LineString>
       </Placemark>
   </Folder>
   <Folder>
       <name>Data Points</name>""")


for i in range(len(year)):
    
    if i == 0:  # first spot and receiver

        f.write("""        <Folder>
            <name>{:s}/{:s}/{:s} {:s}:{:s}:{:s}</name>
            <Placemark>
                <name>{:s}</name>
                <styleUrl>#style</styleUrl>
                <ExtendedData>
                    <Data name="Date"><value>{:s}/{:s}/{:s}</value></Data>
                    <Data name="Time"><value>{:s}:{:s}:{:s}</value></Data>
                    <Data name="Latitude"><value>{:s}</value></Data>
                    <Data name="Longitude"><value>{:s}</value></Data>
                    <Data name="Altitude"><value>{:s}m</value></Data>
                    <Data name="Locator"><value>{:s}</value></Data>
                </ExtendedData>
                <Point>
                    <coordinates>{:s},{:s},{:s}</coordinates>
                </Point>
            </Placemark>""".format(year[i], month[i], day[i], hour[i], minute[i], '00', callsign[i], year[i], month[i], day[i], hour[i], minute[i], '00',\
                              str(latitude[i]), str(longitude[i]), str(altitude[i]), locator[i], str(longitude[i]), str(latitude[i]), str(altitude[i])))
        f.write("""            <Folder>
                <name>Receivers</name>
                <Placemark>
                    <name>{:s}</name>
                    <visibility>0</visibility>
                    <styleUrl>#styleR</styleUrl>
                    <ExtendedData>
                        <Data name="Receiver"><value>{:s}</value></Data>
                        <Data name="Latitude"><value>{:s}</value></Data>
                        <Data name="Longitude"><value>{:s}</value></Data>
                        <Data name="Locator"><value>{:s}</value></Data>
                        <Data name="Distance"><value>{:s}km</value></Data>
                        <Data name="Frequency"><value>{:s}MHz</value></Data>
                        <Data name="SNR"><value>{:s}</value></Data>
                        <Data name="Drift"><value>{:s}Hz</value></Data>
                    </ExtendedData>
                    <Point>
                        <coordinates>{:s},{:s}</coordinates>
                    </Point>
                </Placemark>""".format(receiver[i], receiver[i], str(latitudeR[i]), str(longitudeR[i]), locatorR[i], distance[i], frequency[i], snr[i], drift[i],\
                                       str(longitudeR[i]), str(latitudeR[i])))
        continue
    
    
    if year[i-1] == year[i] and month[i-1] == month[i] and day[i-1] == day[i] and hour[i-1] == hour[i] and minute[i-1] == minute[i]:    # another receiver

        f.write("""                <Placemark>
                    <name>{:s}</name>
                    <visibility>0</visibility>
                    <styleUrl>#styleR</styleUrl>
                    <ExtendedData>
                        <Data name="Receiver"><value>{:s}</value></Data>
                        <Data name="Latitude"><value>{:s}</value></Data>
                        <Data name="Longitude"><value>{:s}</value></Data>
                        <Data name="Locator"><value>{:s}</value></Data>
                        <Data name="Distance"><value>{:s}km</value></Data>
                        <Data name="Frequency"><value>{:s}MHz</value></Data>
                        <Data name="SNR"><value>{:s}</value></Data>
                        <Data name="Drift"><value>{:s}Hz</value></Data>
                    </ExtendedData>
                    <Point>
                        <coordinates>{:s},{:s}</coordinates>
                    </Point>
                </Placemark>""".format(receiver[i], receiver[i], str(latitudeR[i]), str(longitudeR[i]), locatorR[i], distance[i], frequency[i], snr[i], drift[i],\
                                       str(longitudeR[i]), str(latitudeR[i])))

        
    else:   # new spot
                
        f.write("""            </Folder>
        </Folder>
        <Folder>
            <name>{:s}/{:s}/{:s} {:s}:{:s}:{:s}</name>
            <Placemark>
                <name>{:s}</name>
                <styleUrl>#style</styleUrl>
                <ExtendedData>
                    <Data name="Date"><value>{:s}/{:s}/{:s}</value></Data>
                    <Data name="Time"><value>{:s}:{:s}:{:s}</value></Data>
                    <Data name="Latitude"><value>{:s}</value></Data>
                    <Data name="Longitude"><value>{:s}</value></Data>
                    <Data name="Altitude"><value>{:s}</value></Data>
                    <Data name="Locator"><value>{:s}</value></Data>
                </ExtendedData>
                <Point>
                    <coordinates>{:s},{:s},{:s}</coordinates>
                </Point>
            </Placemark>""".format(year[i], month[i], day[i], hour[i], minute[i], '00', callsign[i], year[i], month[i], day[i], hour[i], minute[i], '00',\
                              str(latitude[i]), str(longitude[i]), str(altitude[i]), locator[i], str(longitude[i]), str(latitude[i]), str(altitude[i])))
        f.write("""            <Folder>
                <name>Receivers</name>
                <Placemark>
                    <name>{:s}</name>
                    <visibility>0</visibility>
                    <styleUrl>#styleR</styleUrl>
                    <ExtendedData>
                        <Data name="Receiver"><value>{:s}</value></Data>
                        <Data name="Latitude"><value>{:s}</value></Data>
                        <Data name="Longitude"><value>{:s}</value></Data>
                        <Data name="Locator"><value>{:s}</value></Data>
                        <Data name="Distance"><value>{:s}km</value></Data>
                        <Data name="Frequency"><value>{:s}MHz</value></Data>
                        <Data name="SNR"><value>{:s}</value></Data>
                        <Data name="Drift"><value>{:s}Hz</value></Data>
                    </ExtendedData>
                    <Point>
                        <coordinates>{:s},{:s}</coordinates>
                    </Point>
                </Placemark>""".format(receiver[i], receiver[i], str(latitudeR[i]), str(longitudeR[i]), locatorR[i], distance[i], frequency[i], snr[i], drift[i],\
                                       str(longitudeR[i]), str(latitudeR[i])))


f.write("""            </Folder>
        </Folder>
    </Folder>
</Document>
</kml>""")

f.close()
print "Done."

