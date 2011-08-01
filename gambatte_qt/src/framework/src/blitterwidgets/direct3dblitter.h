/***************************************************************************
 *   Copyright (C) 2008 by Sindre Aam�s                                    *
 *   aamas@stud.ntnu.no                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2 as     *
 *   published by the Free Software Foundation.                            *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License version 2 for more details.                *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   version 2 along with this program; if not, write to the               *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef DIRECT3DBLITTER_H_
#define DIRECT3DBLITTER_H_

#include "../blitterwidget.h"
#include <memory>
#include <d3d9.h>

class QCheckBox;
class QComboBox;

class Direct3DBlitter : public BlitterWidget {
	typedef IDirect3D9* (WINAPI *Direct3DCreate9Ptr)(UINT);

	FtEst ftEst;
	const std::auto_ptr<QWidget> confWidget;
	QComboBox *const adapterSelector;
	QCheckBox *const vblankblitBox;
	QCheckBox *const flippingBox;
	QCheckBox *const triplebufBox;
	QCheckBox *const bfBox;
	HMODULE d3d9handle;
	Direct3DCreate9Ptr direct3DCreate9;
	IDirect3D9 *d3d;
	IDirect3DDevice9* device;
	IDirect3DVertexBuffer9* vertexBuffer;
	IDirect3DTexture9 *stexture;
	IDirect3DTexture9 *vtexture;
	usec_t lastblank;
	unsigned inWidth;
	unsigned inHeight;
	unsigned textRes;
	unsigned backBufferWidth;
	unsigned backBufferHeight;
	unsigned clear;
	unsigned dhz;
	unsigned swapInterval;
	unsigned adapterIndex;
	bool exclusive;
	bool windowed;
	bool drawn;
	//bool vblank;
	bool flipping;
	bool vblankblit;
	bool triplebuf;
	bool bf;

	void getPresentParams(D3DPRESENT_PARAMETERS *presentParams) const;
	void lockTexture();
	void setVertexBuffer();
	void setVideoTexture();
	void setFilter();
	void setDeviceState();
	void resetDevice();
	void exclusiveChange();
	void present();

protected:
	void paintEvent(QPaintEvent *e);
	void resizeEvent(QResizeEvent *e);
	void setBufferDimensions(unsigned w, unsigned h);

public:
	Direct3DBlitter(VideoBufferLocker vbl, QWidget *parent = 0);
	~Direct3DBlitter();
	void init();
	void uninit();
	void blit();
	void draw();
	long sync();
	long frameTimeEst() const;
	void setExclusive(bool exclusive);
	bool isUnusable() const { return !d3d; }
	QWidget* settingsWidget() const { return confWidget.get(); }
	void acceptSettings();
	void rejectSettings() const;

	QPaintEngine* paintEngine () const { return NULL; }
	void setSwapInterval(unsigned si);
	void rateChange(int dhz);
};

#endif /*DIRECT3DBLITTER_H_*/
