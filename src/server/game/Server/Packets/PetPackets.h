/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PetPackets_h__
#define PetPackets_h__

#include "G3D/Vector3.h"
#include "ObjectGuid.h"
#include "Packet.h"

namespace WorldPackets
{
    namespace Pet
    {
        class DismissCritter final : public ClientPacket
        {
        public:
            DismissCritter(WorldPacket&& packet) : ClientPacket(CMSG_DISMISS_CRITTER, std::move(packet)) { }

            void Read() override;

            ObjectGuid CritterGUID;
        };

        class PetAbandon final : public ClientPacket
        {
        public:
            PetAbandon(WorldPacket&& packet) : ClientPacket(CMSG_PET_ABANDON, std::move(packet)) { }

            void Read() override;

            ObjectGuid PetGUID;
        };

        class PetStopAttack final : public ClientPacket
        {
        public:
            PetStopAttack(WorldPacket&& packet) : ClientPacket(CMSG_PET_STOP_ATTACK, std::move(packet)) { }

            void Read() override;

            ObjectGuid PetGUID;
        };

        class PetSpellAutocast final : public ClientPacket
        {
        public:
            PetSpellAutocast(WorldPacket&& packet) : ClientPacket(CMSG_PET_SPELL_AUTOCAST, std::move(packet)) { }

            void Read() override;

            ObjectGuid PetGUID;
            uint32 SpellID = 0;
            bool AutocastEnabled = false;
        };

        class PetLearnedSpell final : public ServerPacket
        {
        public:
            PetLearnedSpell() : ServerPacket(SMSG_PET_LEARNED_SPELL, 4) { }

            WorldPacket const* Write() override;

            uint32 SpellID = 0;
        };

        class PetUnlearnedSpell final : public ServerPacket
        {
        public:
            PetUnlearnedSpell() : ServerPacket(SMSG_PET_UNLEARNED_SPELL, 4) { }

            WorldPacket const* Write() override;

            uint32 SpellID = 0;
        };

        class RequestPetInfo final : public ClientPacket
        {
        public:
            RequestPetInfo(WorldPacket&& packet) : ClientPacket(CMSG_REQUEST_PET_INFO, std::move(packet)) { }

            void Read() override { }
        };

        class PetDismissSound final : public ServerPacket
        {
        public:
            PetDismissSound(int32 modelId, G3D::Vector3 modelPosition)
                : ServerPacket(SMSG_PET_DISMISS_SOUND, 4 + 12), ModelId(modelId), ModelPosition(modelPosition) { }

            WorldPacket const* Write() override;

            int32 ModelId = 0;
            G3D::Vector3 ModelPosition;
        };
    }
}

#endif // PetPackets_h__
