//
//  mds.h
//  Agent11073
//
//  Created by Hugo Arevalo on 6/11/22.
//

#ifndef mds_h
#define mds_h

#include <stdio.h>
#include "../asn1/phd_types.h"

struct MDS {
    ASN1_HANDLE Handle;
    SystemType SystemType;
    SystemModel SystemModel;
    octet_string SystemId;
    ConfigId DevConfigurationId;
    AttrValMap AttributeValueMap;
    ProductionSpec ProductionSpecification;
    MdsTimeInfo MdsTimeInfo;
    AbsoluteTime DateAndTime;
    RelativeTime RelativeTime;
    HighResRelativeTime HiResRelativeTime;
    AbsoluteTimeAdjust DateAndTimeAdjustment;
    PowerStatus PowerStatus;
    BITS_16 BatteryLevel;
    BatMeasure RemainingBatteryTyme;
    RegCertDataList RegCertDataList;
    TypeVerList SystemTypeSpecList;
    RelativeTime ConfirmTimeout;
}

#endif /* mds_h */
