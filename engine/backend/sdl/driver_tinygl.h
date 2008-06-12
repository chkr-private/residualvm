/* Residual - Virtual machine to run LucasArts' 3D adventure games
 * Copyright (C) 2003-2006 The ScummVM-Residual Team (www.scummvm.org)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 * $URL$
 * $Id$
 *
 */

#ifndef BACKEND_DRIVER_TINYGL_H
#define BACKEND_DRIVER_TINYGL_H

#include "common/sys.h"
#include "common/vector3d.h"

#include "engine/color.h"
#include "engine/model.h"
#include "engine/colormap.h"
#include "engine/bitmap.h"
#include "engine/backend/driver.h"
#include "engine/backend/sdl/driver_sdl.h"

#include "engine/tinygl/gl.h"
#include "engine/tinygl/zgl.h"

#include <SDL.h>

class DriverTinyGL : public DriverSDL {
public:
	DriverTinyGL(int screenW, int screenH, int screenBPP, bool fullscreen = false);
	virtual ~DriverTinyGL();

	void setupCamera(float fov, float nclip, float fclip, float roll);
	void positionCamera(Vector3d pos, Vector3d interest);

	void toggleFullscreenMode();
	void clearScreen(); 
	void flipBuffer();

	bool isHardwareAccelerated();

	void startActorDraw(Vector3d pos, float yaw, float pitch, float roll);
	void finishActorDraw();
	void setupShadower(Shadow *shadow);
	
	void set3DMode();

	void translateViewpoint(Vector3d pos, float pitch, float yaw, float roll);
	void translateViewpoint();

	void drawHierachyNode(const Model::HierNode *node);
	void drawModelFace(const Model::Face *face, float *vertices, float *vertNormals, float *textureVerts);

	void disableLights();
	void setupLight(Scene::Light *light, int lightId);

	void createMaterial(Material *material, const char *data, const CMap *cmap);
	void selectMaterial(const Material *material);
	void destroyMaterial(Material *material);

	void createBitmap(Bitmap *bitmap);
	void drawBitmap(const Bitmap *bitmap);
	void destroyBitmap(Bitmap *bitmap);

	void drawDepthBitmap(int x, int y, int w, int h, char *data);
	void drawBitmap();
	void dimScreen();
	void dimRegion(int x, int y, int w, int h, float level);

	Bitmap *getScreenshot(int w, int h);
	void storeDisplay();
	void copyStoredToDisplay();

	void drawEmergString(int x, int y, const char *text, const Color &fgColor);
	void loadEmergFont();
	TextObjectHandle *createTextBitmap(uint8 *bitmap, int width, int height, const Color &fgColor);
	void drawTextBitmap(int x, int y, TextObjectHandle *handle);
	void destroyTextBitmap(TextObjectHandle *handle);

	void drawRectangle(PrimitiveObject *primitive);
	void drawLine(PrimitiveObject *primitive);
	void drawPolygon(PrimitiveObject *primitive);

	void prepareSmushFrame(int width, int height, byte *bitmap);
	void drawSmushFrame(int offsetX, int offsetY);

protected:

private:
	ZBuffer *_zb;
	SDL_Surface *_screen;
	byte *_smushBitmap;
	int _smushWidth;
	int _smushHeight;
	byte *_storedDisplay;
};

#endif
