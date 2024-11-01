/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 * vim: sw=2 ts=4 et :
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef RemoteSandboxBrokerProcessParent_h_
#define RemoteSandboxBrokerProcessParent_h_

#include "mozilla/Attributes.h"
#include "base/basictypes.h"
#include "base/file_path.h"
#include "base/thread.h"
#include "mozilla/ipc/GeckoChildProcessHost.h"

class nsIRunnable;

namespace mozilla {

class RemoteSandboxBrokerProcessParent final
    : public mozilla::ipc::GeckoChildProcessHost {
 public:
  RemoteSandboxBrokerProcessParent();

  RefPtr<ipc::ProcessHandlePromise> AsyncLaunch();

  bool CanShutdown() override { return true; }

  using mozilla::ipc::GeckoChildProcessHost::GetChildProcessHandle;

  // GeckoChildProcessHost does not directly provide `AddHandleToShare` as
  // handles are expected to be passed using `GeckoArgs`. However when
  // `RemoteSandboxBroker` is being used, we have already set up the argument
  // list, so allow adding those handles directly to the broker's launch
  // options.
  void AddHandleToShare(HANDLE aHandle) {
    mLaunchOptions->handles_to_inherit.push_back(aHandle);
  }

 private:
  ~RemoteSandboxBrokerProcessParent();

  DISALLOW_COPY_AND_ASSIGN(RemoteSandboxBrokerProcessParent);
};

}  // namespace mozilla

#endif  // ifndef GMPProcessParent_h
