#pragma once

#include "ByteBuffer.h"
#include <boost/make_shared.hpp>

enum ServerboundPacket {
	ServerboundReply,
	ServerboundSetProjectStatus,
	ServerboundGetExplorerData,
	ServerboundCreateTrack,
	ServerboundRefresh,
	ServerboundMidiMessage,
	ServerboundUpdateTrackInfo,
	ServerboundMidiNotesAdd,
	ServerboundMidiNotesDelete,
	ServerboundMidiNotesEdit,
	ServerboundOpenPluginManager,
	ServerboundConfig,
	ServerboundScanVSTs,
	ServerboundTrackMixerInfo
};

enum ClientboundPacket {
	ClientboundReply,
	ClientboundProjectStatus,
	ClientboundSyncTrackInfo,
	ClientboundTrackMidiData,
	ClientboundUpdateTrackInfo,
	ClientboundConfig,
	ClientboundScanVSTs,
	ClientboundTrackMixerInfo
};

namespace EIMPackets {
	std::shared_ptr<ByteBuffer> makePacket(ClientboundPacket id);
	std::shared_ptr<ByteBuffer> makeReplyPacket(unsigned int id);
	std::shared_ptr<ByteBuffer> makeProjectStatusPacket();
	std::shared_ptr<ByteBuffer> makeTrackMidiDataPacket(int size);
	std::shared_ptr<ByteBuffer> makeAllTrackMidiDataPacket();
	std::shared_ptr<ByteBuffer> makeScanVSTsPacket(bool isScanning);
	std::shared_ptr<ByteBuffer> makeTrackMixerInfoPacket(int size);
	std::shared_ptr<ByteBuffer> makeAllTrackMixerInfoPacket();
}
