/* eos - A reimplementation of BioWare's Aurora engine
 * Copyright (c) 2010 Sven Hesse (DrMcCoy), Matthew Hoops (clone2727)
 *
 * The Infinity, Aurora, Odyssey and Eclipse engines, Copyright (c) BioWare corp.
 * The Electron engine, Copyright (c) Obsidian Entertainment and BioWare corp.
 *
 * This file is part of eos and is distributed under the terms of
 * the GNU General Public Licence. See COPYING for more informations.
 */

/** @file aurora/rimfile.h
 *  Handling BioWare's RIMs (resource archives).
 */

#ifndef AURORA_RIMFILE_H
#define AURORA_RIMFILE_H

#include <vector>

#include "common/types.h"
#include "common/ustring.h"
#include "common/file.h"

#include "aurora/types.h"
#include "aurora/archive.h"
#include "aurora/aurorafile.h"

namespace Common {
	class SeekableReadStream;
	class File;
}

namespace Aurora {

/** Class to hold resource data of a RIM file. */
class RIMFile : public Archive, public AuroraBase {
public:
	RIMFile(const Common::UString &fileName);
	~RIMFile();

	/** Clear the resource list. */
	void clear();

	/** Return the list of resources. */
	const ResourceList &getResources() const;

	/** Return a stream of the resource's contents. */
	Common::SeekableReadStream *getResource(uint32 index) const;

private:
	/** Internal resource information. */
	struct IResource {
		uint32 offset; ///< The offset of the resource within the BIF.
		uint32 size;   ///< The resource's size.
	};

	typedef std::vector<IResource> IResourceList;

	/** External list of resource names and types. */
	ResourceList _resources;

	/** Internal list of resource offsets and sizes. */
	IResourceList _iResources;

	/** The name of the RIM file. */
	Common::UString _fileName;

	void open(Common::File &file) const;

	void load();
	void readResList(Common::SeekableReadStream &rim, uint32 offset);
};

} // End of namespace Aurora

#endif // AURORA_RIMFILE_H
