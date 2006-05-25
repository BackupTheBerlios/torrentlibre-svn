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

#ifndef QalfTORRENTMAKER_H
#define QalfTORRENTMAKER_H

#include <QString>
#include "libtorrent/torrent_info.hpp"
#include "libtorrent/peer_id.hpp"
#include <boost/filesystem/path.hpp>

class QalfTorrentMaker {

	public:
		QalfTorrentMaker() ;
		~QalfTorrentMaker() ;
		QString createTorrent(QString &filename, QString &torrentFilename, QString &tracker) ;
		static QString hashToStr(libtorrent::sha1_hash &hash) ;

	private:
		void addFiles(libtorrent::torrent_info& t, boost::filesystem::path const& p, boost::filesystem::path const& l) ;
};

#endif // QalfTORRENTMAKER_H
