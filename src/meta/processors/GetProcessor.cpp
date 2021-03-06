/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */


#include "meta/processors/GetProcessor.h"

namespace nebula {
namespace meta {

void GetProcessor::process(const cpp2::GetReq& req) {
    CHECK_SEGMENT(req.get_segment());
    auto key = MetaServiceUtils::assembleSegmentKey(req.get_segment(), req.get_key());
    auto result = doGet(key);
    if (!result.ok()) {
        LOG(ERROR) << "Get Failed :" << key << " not found!";
        resp_.set_code(cpp2::ErrorCode::E_NOT_FOUND);
        onFinished();
        return;
    }
    resp_.set_code(cpp2::ErrorCode::SUCCEEDED);
    resp_.set_value(std::move(result.value()));
    onFinished();
}

}  // namespace meta
}  // namespace nebula
