// Copyright 2021 Sony Group Corporation. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PACKAGES_VIDEO_PLAYER_VIDEO_PLAYER_ELINUX_VIDEO_PLAYER_STREAM_HANDLER_IMPL_H_
#define PACKAGES_VIDEO_PLAYER_VIDEO_PLAYER_ELINUX_VIDEO_PLAYER_STREAM_HANDLER_IMPL_H_

#include <functional>

#include "video_player_stream_handler.h"

class VideoPlayerStreamHandlerImpl : public VideoPlayerStreamHandler {
 public:
  using OnNotifyInitialized = std::function<void()>;
  using OnNotifyFrameDecoded = std::function<void()>;
  using OnNotifyCompleted = std::function<void()>;
  using OnNotifyPlaying = std::function<void(bool)>;
  using OnNotifyError = std::function<void()>;

  VideoPlayerStreamHandlerImpl(OnNotifyInitialized on_notify_initialized,
                               OnNotifyFrameDecoded on_notify_frame_decoded,
                               OnNotifyCompleted on_notify_completed,
                               OnNotifyPlaying on_notify_playing,
                               OnNotifyError on_notify_error)
      : on_notify_initialized_(on_notify_initialized),
        on_notify_frame_decoded_(on_notify_frame_decoded),
        on_notify_completed_(on_notify_completed),
        on_notify_playing_(on_notify_playing),
        on_notify_error_(on_notify_error) {}
  virtual ~VideoPlayerStreamHandlerImpl() = default;

  // Prevent copying.
  VideoPlayerStreamHandlerImpl(VideoPlayerStreamHandlerImpl const&) = delete;
  VideoPlayerStreamHandlerImpl& operator=(VideoPlayerStreamHandlerImpl const&) =
      delete;

 protected:
  // |VideoPlayerStreamHandler|
  void OnNotifyInitializedInternal() {
    if (on_notify_initialized_) {
      on_notify_initialized_();
    }
  }

  // |VideoPlayerStreamHandler|
  void OnNotifyFrameDecodedInternal() {
    if (on_notify_frame_decoded_) {
      on_notify_frame_decoded_();
    }
  }

  // |VideoPlayerStreamHandler|
  void OnNotifyCompletedInternal() {
    if (on_notify_completed_) {
      on_notify_completed_();
    }
  }

  void OnNotifyPlayingInternal(bool is_playing) {
    if (on_notify_playing_) {
      on_notify_playing_(is_playing);
    }
  }

  void OnNotifyErrorInternal(){
    if(on_notify_error_){
      on_notify_error_();
    }
  }

  OnNotifyInitialized on_notify_initialized_;
  OnNotifyFrameDecoded on_notify_frame_decoded_;
  OnNotifyCompleted on_notify_completed_;
  OnNotifyPlaying on_notify_playing_;
  OnNotifyError on_notify_error_;
};

#endif  // PACKAGES_VIDEO_PLAYER_VIDEO_PLAYER_ELINUX_VIDEO_PLAYER_STREAM_HANDLER_IMPL_H_
