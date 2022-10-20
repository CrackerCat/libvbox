/* This file is part of libvbox
 * Copyright (C) 2022  Michael Hansen
 *
 * libvbox is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * libvbox is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with libvbox; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "libvbox_p.h"

#if VirtualBoxSDK_VERSION >= VBox_MAKE_VERSION(7, 0, 0)
COM_WRAP_IFC(IAudioSettings)

VBox::COMPtr<VBox::IAudioAdapter> VBox::IAudioSettings::adapter() const
{
    COMPtr<IAudioAdapter> result;
    COM_GetValue_Wrap(get_IFC(), Adapter, result);
    return result;
}

VBox::COMPtr<VBox::IHostAudioDevice>
VBox::IAudioSettings::getHostAudioDevice(AudioDirection usage)
{
    ::IHostAudioDevice *cResult = nullptr;

    auto rc = get_IFC()->GetHostAudioDevice(
                static_cast<COM_Enum(::AudioDirection)>(usage), &cResult);
    COM_ERROR_CHECK(rc);

    return COMPtr<IHostAudioDevice>::wrap(cResult);
}

void VBox::IAudioSettings::setHostAudioDevice(
        const COMPtr<IHostAudioDevice> &device, AudioDirection usage)
{
    auto rc = get_IFC()->SetHostAudioDevice(device->get_IFC(),
                static_cast<COM_Enum(::AudioDirection)>(usage));
    COM_ERROR_CHECK(rc);
}
#endif
