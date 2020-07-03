/******************************************************************************
 *
 *  Copyright 2020 NXP
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/
#include <log/log.h>

#include "NxpNfcLegacy.h"

#include "phNfcStatus.h"
#include "NfcApiGet.h"
#include "phNxpNciHal_Common.h"

extern bool nfc_debug_enabled;

namespace vendor {
namespace nxp {
namespace nxpnfclegacy {
namespace V1_0 {
namespace implementation {


Return<uint8_t>
NxpNfcLegacy::setEseState(NxpNfcHalEseState EseState) {
  NFCSTATUS status = NFCSTATUS_FAILED;
  ALOGD("NxpNfcLegacy::setEseState Entry");

  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
      /*
       * In the case of a failure, return status failed.
       */
       return status;
  }


  if(EseState == NxpNfcHalEseState::HAL_NFC_ESE_IDLE_MODE)
  {
    ALOGD("NxpNfcLegacy::setEseState state == HAL_NFC_ESE_IDLE_MODE");
    status = hal_api_s->phNxpNciHal_setEseState(phNxpNciHalNfc_e_SetIdleMode);
  }
  if (EseState == NxpNfcHalEseState::HAL_NFC_ESE_WIRED_MODE) {
    ALOGD("NxpNfcLegacy::setEseState state == HAL_NFC_ESE_WIRED_MODE");
    status = hal_api_s->phNxpNciHal_setEseState(phNxpNciHalNfc_e_SetWiredMode);
  }

  ALOGD("NxpNfcLegacy::setEseState Exit");
  return status;
}

Return<uint8_t>
NxpNfcLegacy::getchipType() {
  uint8_t chiptype = 0;
  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return 0;
  }

  ALOGD("NxpNfcLegacy::getchipType Entry");
  chiptype = hal_api_s->phNxpHal_getchipType();
  ALOGD("NxpNfcLegacy::getchipType Exit");
  return chiptype;
}

Return<uint16_t>
NxpNfcLegacy::setNfcServicePid(uint64_t pid) {
  NFCSTATUS status = NFCSTATUS_FAILED;
  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return status;
  }

  ALOGD("NxpNfcLegacy::setNfcServicePid Entry");
  status = hal_api_s->phNxpNciHal_setNfcServicePid(pid);
  ALOGD("NxpNfcLegacy::setNfcServicePid Exit");
  return status;
}

Return<uint16_t>
NxpNfcLegacy::getEseState() {
  NFCSTATUS status = NFCSTATUS_FAILED;
  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return status;
  }

  ALOGD("NxpNfcLegacy::getEseState Entry");
  status = hal_api_s->phNxpNciHal_getEseState();
  ALOGD("NxpNfcLegacy::getEseState Exit");
  return status;
}

Return<uint16_t>
NxpNfcLegacy::spiDwpSync(uint32_t level) {
  uint16_t status = 0;
  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return status;
  }

  ALOGD("NxpNfcLegacy::spiDwpSync Entry");
  status = hal_api_s->phNxpNciHal_ReleaseSVDDWait(level);

  ALOGD("NxpNfcLegacy::spiDwpSync Exit");
  return status;
}

Return<uint16_t>
NxpNfcLegacy::RelForceDwpOnOffWait(uint32_t level) {
  uint16_t status = 0;
  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return status;
  }

  ALOGD("NxpNfcLegacy::RelForceDwpOnOffWait Entry");
  status = hal_api_s->phNxpNciHal_ReleaseDWPOnOffWait(level);

  ALOGD("NxpNfcLegacy::RelForceDwpOnOffWait Exit");
  return status;
}

Return<int8_t>
NxpNfcLegacy::getSPMStatus(uint32_t level) {
  int8_t status = -1;
  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return status;
  }

  ALOGD("NxpNfcLegacy::getSPMStatus Entry");
  status = hal_api_s->phNxpNciHal_getSPMStatus(level);

  ALOGD("NxpNfcLegacy::getSPMStatus Exit");
  return status;
}

Return<int32_t>
NxpNfcLegacy::hciInitUpdateState(NfcHciInitStatus HciStatus) {
  int32_t status = 0;
  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return status;
  }

  ALOGD("NxpNfcLegacy::hciInitUpdateState Entry");
  if (HciStatus == NfcHciInitStatus::NFC_HCI_INIT_START)
  {
    ALOGD("NxpNfcLegacy::hciInitUpdateState state == NFC_HCI_INIT_START");
    hal_api_s->phNxpNciHal_hciInitUpdateState(phNxpNfcHciInitStatus_e_Start);
  }
  else if (HciStatus == NfcHciInitStatus::NFC_HCI_INIT_COMPLETE)
  {
    ALOGD("NxpNfcLegacy::hciInitUpdateState state == NFC_HCI_INIT_COMPLETE");
    hal_api_s->phNxpNciHal_hciInitUpdateState(phNxpNfcHciInitStatus_e_Complete);
  }
  ALOGD("NxpNfcLegacy::hciInitUpdateState Exit");
  return status;
}

Return<int32_t>
NxpNfcLegacy::hciInitUpdateStateComplete() {
  int32_t status = 0;
  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return status;
  }

  ALOGD("NxpNfcLegacy::hciInitUpdateStateComplete Entry");

  status = hal_api_s->phNxpNciHal_hciInitUpdateStateComplete();

  ALOGD("NxpNfcLegacy::hciInitUpdateStateComplete Exit");

  return status;
}

Return<void> NxpNfcLegacy::getCachedNfccConfig(getCachedNfccConfig_cb _hidl_cb){
  phNxpNci_getCfg_info_t GetCfg_info;
  NxpNciCfgInfo ConfigData;
  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return Void();
  }
  ALOGD("NxpNfcLegacy::GetCachedNfccConfig Entry" );

  hal_api_s->phNxpNciHal_GetCachedNfccConfig(&GetCfg_info);
  memcpy(&ConfigData,&GetCfg_info,sizeof(NxpNciCfgInfo));
  _hidl_cb(ConfigData);

  ALOGD("NxpNfcLegacy::GetCachedNfccConfig Exit");
  return Void();
}

Return<void> NxpNfcLegacy::getNxpConfig(getNxpConfig_cb _hidl_cb)
{
  phNxpNfcHalConfig localConfigData;
  NxpNfcHalConfig config;
  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return Void();
  }

  ALOGD("NxpNfcLegacy::getNxpConfig Entry" );
  hal_api_s->phNxpNciHal_getNxpConfig(&localConfigData);
  memcpy(&config, &localConfigData, sizeof(NxpNfcHalConfig));
  _hidl_cb(config);
  ALOGD("NxpNfcLegacy::getNxpConfig Exit");
  return Void();
}

Return<void> NxpNfcLegacy::nciTransceive( const NxpNciExtnCmd &NciCmd,nciTransceive_cb _hidl_cb){
  phNxpNci_Extn_Cmd_t  in;
  phNxpNci_Extn_Resp_t out;

  NxpNciExtnResp nciResp;

  hal_api_struct_t *hal_api_s = getHalApiStruct();
  if (hal_api_s == nullptr){
       return Void();
  }

  ALOGD("NxpNfcLegacy::NciTransceive Entry" );

  memcpy(&in,&NciCmd,sizeof(NxpNciExtnCmd));

  hal_api_s->phNxpNciHal_nciTransceive(&in,&out);

  memcpy(&nciResp,&out,sizeof(NxpNciExtnResp));

  _hidl_cb(nciResp);

  ALOGD("NxpNfcLegacy::NciTransceive Exit");
  return Void();
}


}  // namespace implementation
}  // namespace V1_0
}  // namespace nxpnfclegacy
}  // namespace nxp
}  // namespace vendor
