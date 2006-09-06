/*******************************************************
** Copyright (C) 2006 Francois Gaudin.
**
** Torrentlibre is free software; you can redistribute
** it and/or modify it under the terms of the GNU
** Library General Public License as published by the
** Free Software Foundation; either version 2, or (at
** your option) any later version.
**
********************************************************/

#include "qalftorrent.h"
// #include "qalfconfig.h"
// #include <QVector>
// #include <iostream>
// #include <fstream>
// #include <iterator>
// #include <iomanip>

#include "libtorrent/entry.hpp"
#include "libtorrent/bencode.hpp"
// #include "libtorrent/file.hpp"
// #include "libtorrent/storage.hpp"
// #include "libtorrent/hasher.hpp"

// #include <boost/filesystem/operations.hpp>
#include <boost/filesystem/fstream.hpp>

using namespace boost::filesystem;
using namespace libtorrent;

QalfTorrent::QalfTorrent(QByteArray &torrentData) {
	const char * rawData = torrentData.constData() ;
	entry e = bdecode(rawData, rawData + torrentData.length());
	torrent = torrent_info(e) ;
}

QalfTorrent::~QalfTorrent() {

}

// QString QalfTorrentMaker::createTorrent(QString &filename, QString &torrentFilename, QString &tracker) {
// 	using namespace libtorrent;
// 	using namespace boost::filesystem;
// 
// 	QString hashStr ;
// 
// 	try {
// 		torrent_info t;
// 		path full_path = path(filename.toLocal8Bit());
// 		ofstream out(path(torrentFilename.toLocal8Bit()), std::ios_base::binary);
// 
// 		int piece_size = 256 * 1024;
// 		QalfConfig * config = QalfConfig::getConfigObject() ;
// 		QString usernameProperty("username") ;
// 		QString creator = config->getProperty(usernameProperty) ;
// 
// 		addFiles(t, full_path.branch_path(), full_path.leaf());
// 		t.set_piece_size(piece_size);
// 
// 		storage st(t, full_path.branch_path());
// 		char const * trackerStr = tracker.toLocal8Bit() ;
// 		t.add_tracker(trackerStr);
// 
// 		// calculate the hash for all pieces
// 		int num = t.num_pieces();
// 		QVector<char> buf(piece_size);
// 		for (int i = 0; i < num; ++i) {
// 			st.read(&buf[0], i, 0, t.piece_size(i));
// 			hasher h(&buf[0], t.piece_size(i));
// 			t.set_hash(i, h.final());
// 		}
// 
// 		t.set_creator(creator.toLocal8Bit());
// 
// 		// create the torrent and print it to out
// 		entry e = t.create_torrent();
// 		sha1_hash hash = t.info_hash() ;
// 		hashStr = hashToStr(hash) ;
// 		
// 		libtorrent::bencode(std::ostream_iterator<char>(out), e);
// 	}
// 	catch (std::exception& e)
// 	{
// 		std::cerr << e.what() << "\n";
// 	}
// 
// 	return hashStr ;
// }
// 
// void QalfTorrentMaker::addFiles(torrent_info& t, path const& p, path const& l)
// {
// 	path f(p / l);
// 	if (is_directory(f))
// 	{
// 		for (directory_iterator i(f), end; i != end; ++i)
// 		addFiles(t, p, l / i->leaf());
// 	}
// 	else
// 	{
// 		std::cerr << "adding \"" << l.string() << "\"\n";
// 		file fi(f, file::in);
// 		fi.seek(0, file::end);
// 		libtorrent::size_type size = fi.tell();
// 		t.add_file(l, size);
// 	}
// }
// 
QString QalfTorrent::hashToStr() {
	unsigned char * character ;
	QString hashStr ;
	sha1_hash hash = torrent.info_hash() ;
	
	for(character = hash.begin();character < hash.end();++character) {
		int charToInt = static_cast<int>(*character) ;
		int x16_1 = charToInt/16 ;
		int x16_0 = charToInt%16 ;
		int x16 = x16_1 ;
		bool firstPass = true ;
		while(true) {
			switch(x16) {
				case 10:
					hashStr += 'a' ;
					break;
				case 11:
					hashStr += 'b' ;
					break;
				case 12:
					hashStr += 'c' ;
					break;
				case 13:
					hashStr += 'd' ;
					break;
				case 14:
					hashStr += 'e' ;
					break;
				case 15:
					hashStr += 'f' ;
					break;
				default:
					hashStr += QString::number(x16) ;
					break;
			}
			if(firstPass) {
				firstPass = false ;
			} else {
				break ;
			}
			x16 = x16_0 ;
		}
	}
	return hashStr ;
}
