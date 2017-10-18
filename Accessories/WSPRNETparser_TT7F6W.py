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
receivers = []

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


# Receivers
rec = []

for i in range(len(year)):

    if i == 0:  # first
        rec.append(receiver[i] + ' ' + locatorR[i] + ' ' + str(distance[i]) + 'km, ')

        if len(year) == 1:
            receivers.append(''.join(rec))
            break
        else:
            continue

    if year[i] == year[i-1] and month[i] == month[i-1] and day[i] == day[i-1] and hour[i] == hour[i-1] and minute[i] == minute[i-1]:
        pass
    else:   # new spot
        receivers.append(''.join(rec))
        rec[:] = []

    if i == len(year) - 1:  # last
        rec.append(receiver[i] + ' ' + locatorR[i] + ' ' + str(distance[i]) + 'km, ')
        receivers.append(''.join(rec))
        break

    rec.append(receiver[i] + ' ' + locatorR[i] + ' ' + str(distance[i]) + 'km, ')  # another receiver for the same spot


# KML
f = open('TT7F6WdataW.kml', 'w')

f.write("""<?xml version="1.0" encoding="UTF-8"?>\n""")
f.write("""<kml xmlns="http://earth.google.com/kml/2.0">\n""")
f.write("""<Document>\n""")
f.write("""   <name>{:s}</name>\n""".format(callsign[0]))
f.write("""   <description>The flight path of TT7F6W superpressure balloon.</description>\n""")
f.write("""   <Style id="styleL">\n""")
f.write("""       <LineStyle>\n""")
f.write("""           <color>6414F0FF</color>\n""")
f.write("""           <width>2</width>\n""")
f.write("""       </LineStyle>\n""")
f.write("""       <PolyStyle>\n""")
f.write("""           <color>2d14F0FF</color>\n""")
f.write("""       </PolyStyle>\n""")
f.write("""   </Style>\n""")
f.write("""   <Style id="style">\n""")
f.write("""       <IconStyle>\n""")
f.write("""           <scale>0.25</scale>\n""")
f.write("""           <Icon>\n""")
f.write("""               <href>http://maps.google.com/mapfiles/kml/paddle/ylw-blank-lv.png</href>\n""")
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
                    <B>Locator:</B> $[Locator]<br/>
                    <P>
                    <B>Receivers:</B> $[Receivers]<br/>
                ]]>\n""")
f.write("""           </text>\n""")
f.write("""       </BalloonStyle>\n""")
f.write("""   </Style>\n""")
f.write("""   <Folder>\n""")
f.write("""       <name>Flight Path WSPR</name>\n""")
f.write("""       <Placemark>\n""")
f.write("""           <name>Flight Path</name>\n""")
f.write("""           <styleUrl>#styleL</styleUrl>\n""")
f.write("""           <LineString>\n""")
f.write("""               <extrude>1</extrude>\n""")
f.write("""               <tessellate>1</tessellate>\n""")
f.write("""               <altitudeMode>absolute</altitudeMode>\n""")
f.write("""               <coordinates>\n""")

for i in range(len(year)):

    if i == 0:
        f.write("""                   {:s},{:s},{:s}\n""".format(str(longitude[i]), str(latitude[i]), str(altitude[i])))
        continue
    
    if year[i-1] == year[i] and month[i-1] == month[i] and day[i-1] == day[i] and hour[i-1] == hour[i] and minute[i-1] == minute[i]:
        continue
    else:
        f.write("""                   {:s},{:s},{:s}\n""".format(str(longitude[i]), str(latitude[i]), str(altitude[i])))

f.write("""               </coordinates>\n""")
f.write("""           </LineString>\n""")
f.write("""       </Placemark>\n""")
f.write("""   </Folder>\n""")
f.write("""   <Folder>\n""")
f.write("""       <name>Data Points</name>\n""")

r = 0

for i in range(len(year)):
    
    if i == 0:

        f.write("""       <Placemark>
           <description>{:s}</description>
           <styleUrl>#style</styleUrl>
           <ExtendedData>
               <Data name="Date"><value>{:s}/{:s}/{:s}</value></Data>
               <Data name="Time"><value>{:s}:{:s}:{:s}</value></Data>
               <Data name="Latitude"><value>{:s}</value></Data>
               <Data name="Longitude"><value>{:s}</value></Data>
               <Data name="Altitude"><value>{:s}</value></Data>
               <Data name="Locator"><value>{:s}</value></Data>
               <Data name="Receivers"><value>{:s}</value></Data>
           </ExtendedData>
           <Point>\n
               <coordinates>
                   {:s},{:s},{:s}
               </coordinates>
           </Point>
       </Placemark>""".format(callsign[i], year[i], month[i], day[i], hour[i], minute[i], \
                                 '00', str(latitude[i]), str(longitude[i]), str(altitude[i]), \
                                locator[i], receivers[r], str(longitude[i]), str(latitude[i]), str(altitude[i])))

        continue

    if year[i-1] == year[i] and month[i-1] == month[i] and day[i-1] == day[i] and hour[i-1] == hour[i] and minute[i-1] == minute[i]:
        continue
    else:
        r += 1
        f.write("""       <Placemark>
           <description>{:s}</description>
           <styleUrl>#style</styleUrl>
           <ExtendedData>
               <Data name="Date"><value>{:s}/{:s}/{:s}</value></Data>
               <Data name="Time"><value>{:s}:{:s}:{:s}</value></Data>
               <Data name="Latitude"><value>{:s}</value></Data>
               <Data name="Longitude"><value>{:s}</value></Data>
               <Data name="Altitude"><value>{:s}</value></Data>
               <Data name="Locator"><value>{:s}</value></Data>
               <Data name="Receivers"><value>{:s}</value></Data>
           </ExtendedData>
           <Point>\n
               <coordinates>
                   {:s},{:s},{:s}
               </coordinates>
           </Point>
       </Placemark>""".format(callsign[i], year[i], month[i], day[i], hour[i], minute[i], \
                                 '00', str(latitude[i]), str(longitude[i]), str(altitude[i]), \
                                locator[i], receivers[r], str(longitude[i]), str(latitude[i]), str(altitude[i])))

f.write("""   </Folder>\n""")
f.write("""</Document>\n""")
f.write("""</kml>\n""")

f.close()
print "Done."

