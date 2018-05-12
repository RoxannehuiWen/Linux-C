all:
%:
	mkdir /usr/local/netradio
	mkdir /usr/local/netradio/00001.channel
	mkdir /usr/local/netradio/00002.channel
	mkdir /usr/local/netradio/00003.channel
	touch /usr/local/netradio/00001.channel/desc.txt
	touch /usr/local/netradio/00002.channel/desc.txt
	touch /usr/local/netradio/00003.channel/desc.txt
	echo Classic > /usr/local/netradio/00001.channel/desc.txt
	echo Populor > /usr/local/netradio/00002.channel/desc.txt
	echo Rock > /usr/local/netradio/00003.channel/desc.txt
	

	cp ./music/classic.mp3 /usr/local/netradio/00001.channel
	cp ./music/populor.mp3 /usr/local/netradio/00002.channel
	cp ./music/rock.mp3 /usr/local/netradio/00003.channel
clean:
	
		rm -f *~ radio_client radio_server
		rm -rf /usr/local/netradio
