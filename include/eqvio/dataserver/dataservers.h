#pragma once

#include "eqvio/dataserver/APDatasetReader.h"
#include "eqvio/dataserver/ASLDatasetReader.h"
#include "eqvio/dataserver/DatasetReaderBase.h"
#include "eqvio/dataserver/UZHFPVDatasetReader.h"

#include "eqvio/dataserver/SimpleDataServer.h"
#include "eqvio/dataserver/ThreadedDataServer.h"

#if EQVIO_BUILD_ROSBAG
#include "eqvio/dataserver/HiltiDatasetReader.h"
#include "eqvio/dataserver/RosbagDatasetReader.h"
#endif

inline std::unique_ptr<DatasetReaderBase> createDatasetReader(
    const std::string& dataMode, const std::string& datasetFileName, const double& cameraLag = 0.0,
    const YAML::Node& simulatorConfig = YAML::Node()) {
    std::unique_ptr<DatasetReaderBase> datasetReader;

    if (dataMode == "asl") {
        if (simulatorConfig) {
            datasetReader = std::make_unique<ASLDatasetReader>(datasetFileName, simulatorConfig);
        } else {
            datasetReader = std::make_unique<ASLDatasetReader>(datasetFileName);
        }
    } else if (dataMode == "anu") {
        datasetReader = std::make_unique<APDatasetReader>(datasetFileName);
    } else if (dataMode == "uzhfpv") {
        datasetReader = std::make_unique<UZHFPVDatasetReader>(datasetFileName);
    }
#if EQVIO_BUILD_ROSBAG
    else if (dataMode == "ros") {
        datasetReader = std::make_unique<RosbagDatasetReader>(datasetFileName);
    } else if (dataMode == "hilti") {
        datasetReader = std::make_unique<HiltiDatasetReader>(datasetFileName);
    }
#endif

    datasetReader->cameraLag = cameraLag;
    return datasetReader;
}