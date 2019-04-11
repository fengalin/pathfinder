// pathfinder/demo/magicleap/src/landscape.h
//
// Copyright © 2019 The Pathfinder Project Developers.
//
// Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
// http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
// <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
// option. This file may not be copied, modified, or distributed
// except according to those terms.
//
// A launcher for the ML1 pathfinder demo

// Based on code generated by the Magic Leap Lumin Runtime Editor.
// Original copyright:

// Copyright (c) 2018 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Creator Agreement, located
// here: https://id.magicleap.com/creator-terms

#include <EGL/egl.h>
#include <lumin/LandscapeApp.h>
#include <lumin/Prism.h>
#include <lumin/event/ServerEvent.h>
#include <SceneDescriptor.h>
#include <PrismSceneManager.h>

const uint32_t NUM_QUADS = 6;

/**
 * PathfinderDemo Landscape Application
 */
class PathfinderDemo : public lumin::LandscapeApp {
public:
  /**
   * Constructs the Landscape Application.
   */
  PathfinderDemo();

  /**
   * Destroys the Landscape Application.
   */
  virtual ~PathfinderDemo();

  /**
   * Disallows the copy constructor.
   */
  PathfinderDemo(const PathfinderDemo&) = delete;

  /**
   * Disallows the move constructor.
   */
  PathfinderDemo(PathfinderDemo&&) = delete;

  /**
   * Disallows the copy assignment operator.
   */
  PathfinderDemo& operator=(const PathfinderDemo&) = delete;

  /**
   * Disallows the move assignment operator.
   */
  PathfinderDemo& operator=(PathfinderDemo&&) = delete;

protected:
  /**
   * Initializes the Landscape Application.
   * @return - 0 on success, error code on failure.
   */
  int init() override;

  /**
   * Deinitializes the Landscape Application.
   * @return - 0 on success, error code on failure.
   */
  int deInit() override;

  /**
   * Returns the initial size of the Prism
   * Used in createPrism().
   */
  const glm::vec3 getInitialPrismSize() const;

  /**
   * Creates the prism, updates the private variable prism_ with the created prism.
   */
  void createInitialPrism();

  /**
   * Initializes and creates the scene of all scenes marked as initially instanced
   */
  void spawnInitialScenes();

  /**
   * Respond to a click
   */
  bool onClick();

  /**
   * Dispatch an SVG file to the immersive app
   */
  void dispatch(const char* svg_filename);

  /**
   * Render a node in the scene
   */
  void renderNode(lumin::NodeIDType node_id);

  /**
   * Run application login
   */
  virtual bool updateLoop(float fDelta) override;

  /**
   * Handle events from the server
   */
  virtual bool eventListener(lumin::ServerEvent* event) override;

private:
  lumin::Prism* prism_ = nullptr;  // represents the bounded space where the App renders.
  PrismSceneManager* prismSceneManager_ = nullptr;
  void* pathfinder_ = nullptr;  
  lumin::NodeIDType quad_nodes_[NUM_QUADS] = {lumin::INVALID_NODE_ID};
  lumin::NodeIDType highlighted_node_ = lumin::INVALID_NODE_ID;
  lumin::NodeIDType focus_node_ = lumin::INVALID_NODE_ID;
};

typedef struct MagicLeapPathfinderRenderOptions {
  EGLDisplay display;
  EGLSurface surface;
  float bg_color[4];
  uint32_t viewport[4];
  const char* svg_filename;
} MagicLeapPathfinderRenderOptions;

extern "C" void* magicleap_pathfinder_init();
extern "C" void magicleap_pathfinder_render(void*, MagicLeapPathfinderRenderOptions*);
extern "C" void magicleap_pathfinder_deinit(void*);
