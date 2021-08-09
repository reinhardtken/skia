/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "example/HelloWorldSoftware.h"

#include "include/core/SkCanvas.h"
#include "include/core/SkFont.h"
#include "include/core/SkGraphics.h"
#include "include/core/SkSurface.h"
#include "include/effects/SkGradientShader.h"

#include "include/effects/SkImageFilters.h"

#include <iostream>

using namespace sk_app;

Application* Application::Create(int argc, char** argv, void* platformData) {
    return new HelloWorldSoftware(argc, argv, platformData);
}

HelloWorldSoftware::HelloWorldSoftware(int argc, char** argv, void* platformData)
        // : fBackendType(Window::kNativeGL_BackendType)
        : fBackendType(Window::kRaster_BackendType), fRotationAngle(0) {
    SkGraphics::Init();

    fWindow = Window::CreateNativeWindow(platformData);
    fWindow->setRequestedDisplayParams(DisplayParams());

    // register callbacks
    fWindow->pushLayer(this);

    fWindow->attach(fBackendType);
}

HelloWorldSoftware::~HelloWorldSoftware() {
    fWindow->detach();
    delete fWindow;
}

void HelloWorldSoftware::updateTitle() {
    if (!fWindow || fWindow->sampleCount() <= 1) {
        return;
    }

    SkString title("Hello World ");
    title.append(Window::kRaster_BackendType == fBackendType ? "Raster" : "OpenGL");
    fWindow->setTitle(title.c_str());
}

void HelloWorldSoftware::onBackendCreated() {
    this->updateTitle();
    fWindow->show();
    fWindow->inval();
}

void draw_translate(SkCanvas* canvas) {
    SkPaint paint;
    SkRect rect = {0, 0, 25, 25};
    canvas->save();
    canvas->translate(50, 50);
    canvas->drawRect(rect, paint);
    canvas->restore();
}

void draw_translate2(SkCanvas* canvas) {
    SkPaint paint;
    SkRect rect = {0, 0, 25, 25};
    canvas->save();
    canvas->translate(50, 50);
    canvas->save();
    canvas->translate(50, 50);
    canvas->drawRect(rect, paint);
    canvas->restore();
    canvas->restore();
}

void draw_rotate(SkCanvas* canvas) {
    SkPaint paint;
    SkRect rect = {0, 0, 25, 25};
    canvas->save();
    canvas->translate(150, 150);
    canvas->rotate(45);
    canvas->drawRect(rect, paint);
    canvas->restore();
}

void draw_horizontal_line(SkCanvas* canvas) {
    SkPaint paint;

    canvas->drawLine(100, 100, 300, 100, paint);
}

void draw_vertical_line(SkCanvas* canvas) {
    SkPaint paint;

    canvas->drawLine(100, 100, 100, 300, paint);
}

void draw_oblique_line(SkCanvas* canvas) {
    SkPaint paint;

    canvas->drawLine(100, 100, 300, 300, paint);
}

void draw_width_horizontal_line(SkCanvas* canvas) {
    SkPaint paint;
    paint.setStrokeWidth(15);
    paint.setStrokeCap(SkPaint::kButt_Cap);
    canvas->drawLine(100, 100, 300, 100, paint);
}

void draw_triangle(SkCanvas* canvas) {
    SkPaint paint;
    SkPath path;
    /*一个三角形*/
    path.moveTo(300, 0);    //创建点(300,0)，并记录verb为kMove_Verb
    path.lineTo(400, 100);  //创建点(400,100)，并记录verb为kLine_Verb
    path.lineTo(200, 100);  //创建点(200,100)，并记录verb为kLine_Verb
    path.close();           //闭合path，记录verb为kClose_Verb
    canvas->drawPath(path, paint);
}

void draw_triangle2(SkCanvas* canvas) {
    SkPaint paint;
    SkPath path;
    path.moveTo(300, 100);
    path.lineTo(400, 0);
    path.lineTo(200, 0);
    path.close();
    canvas->drawPath(path, paint);
}

void draw_triangle3(SkCanvas* canvas) {
    SkPaint paint;
    SkPath path;
    path.moveTo(300, 0);
    path.lineTo(400, 100);
    path.lineTo(300, 200);
    path.close();
    canvas->drawPath(path, paint);
}

void draw_triangle4(SkCanvas* canvas) {
    SkPaint paint;
    SkPath path;
    path.moveTo(300, 0);
    path.lineTo(200, 100);
    path.lineTo(300, 200);
    path.close();
    canvas->drawPath(path, paint);
}

void draw_bezier(SkCanvas* canvas) {
    canvas->drawColor(SK_ColorWHITE);

    SkPaint paint;
    paint.setStyle(SkPaint::kStroke_Style);
    // paint.setStrokeWidth(8);
    paint.setColor(0xff4285F4);
    //    paint.setAntiAlias(true);
    //    paint.setStrokeCap(SkPaint::kRound_Cap);

    SkPaint paint2;
    paint2.setColor(SK_ColorRED);
    canvas->drawLine(SkPoint::Make(100, 100), SkPoint::Make(400, 100), paint2);
    canvas->drawLine(SkPoint::Make(400, 100), SkPoint::Make(400, 400), paint2);

    SkPath path;
    path.moveTo(100, 100);
    path.quadTo(400, 100, 400, 400);
    // path.quadTo(10, 192, 250, 250);
    canvas->drawPath(path, paint);

    SkPoint tmp[] = {
            SkPoint::Make(100.000000, 100.000000),
            SkPoint::Make(136.328125, 101.171875),
            SkPoint::Make(170.312500, 104.687500),
            SkPoint::Make(201.953125, 110.546875),
            SkPoint::Make(231.250000, 118.750000),
            SkPoint::Make(258.203125, 129.296875),
            SkPoint::Make(282.812500, 142.187500),
            SkPoint::Make(305.078125, 157.421875),
            SkPoint::Make(325.000000, 175.000000),
            SkPoint::Make(342.578125, 194.921875),
            SkPoint::Make(357.812500, 217.187500),
            SkPoint::Make(370.703125, 241.796875),
            SkPoint::Make(381.250000, 268.750000),
            SkPoint::Make(389.453125, 298.046875),
            SkPoint::Make(395.312500, 329.687500),
            SkPoint::Make(398.828125, 363.671875),
            SkPoint::Make(400.000000, 400.000000),
    };

    SkPaint paint3;
    paint3.setStrokeWidth(3);
    for (int i = 0; i < (sizeof(tmp) / sizeof(tmp[0])); i++) {
        canvas->drawPoint(tmp[i], paint3);
    }

}

void draw_bezier2(SkCanvas* canvas) {
    SkPaint paint;
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setColor(0xff4285F4);

    SkPath path;
    path.moveTo(400, 125);
    path.conicTo(SkPoint::Make(400, 250), SkPoint::Make(200, 250), SK_ScalarRoot2Over2);
    canvas->drawPath(path, paint);
}

void draw_oval(SkCanvas* canvas) { 
  SkPaint paint;
    SkRect rect = {0, 0, 400, 250};
  canvas->drawOval(rect, paint);
}

void draw_save(SkCanvas* canvas) {
    SkPaint paint;
    SkRect rect = {0, 0, 25, 25};
    canvas->drawRect(rect, paint);
    canvas->save();
    canvas->translate(50, 50);
    canvas->drawRect(rect, paint);
    canvas->restore();
    paint.setColor(SK_ColorRED);
    canvas->drawRect(rect, paint);
}

void draw_saveLayer(SkCanvas* canvas) {
    SkPaint paint, blur;
    SkRect rect = {25, 25, 50, 50};
    canvas->drawRect(rect, paint);
    blur.setImageFilter(SkImageFilters::Blur(3, 3, nullptr));
    canvas->saveLayer(nullptr, &blur);

    canvas->translate(50, 50);
    paint.setColor(SK_ColorRED);
    canvas->drawRect(rect, paint);
    canvas->restore();
    SkRect rect2 = {150, 150, 175, 175};
    canvas->drawRect(rect2, paint);
}

static bool once = true;

void HelloWorldSoftware::onPaint(SkSurface* surface) {
    // SkM44 tmp(1, 2, 3, 4,
    //                     5, 6, 7, 8,
    //                     9, 10, 11, 12,
    //                     13, 14, 15, 16);
    // tmp.dump();
    // tmp.preTranslate(2, 3, 4);
    // tmp.dump();

    auto canvas = surface->getCanvas();
    // Clear background
    canvas->clear(SK_ColorWHITE);

    // draw_translate(canvas);
    //    draw_translate2(canvas);
    //    draw_rotate(canvas);
    // draw_triangle(canvas);
    // draw_triangle2(canvas);
    // draw_triangle3(canvas);
    //    draw_triangle4(canvas);
    //draw_horizontal_line(canvas);
    // draw_vertical_line(canvas);
    // draw_oblique_line(canvas);
    //draw_width_horizontal_line(canvas);
    //draw_bezier(canvas);
    //draw_oval(canvas);
    draw_bezier2(canvas);

    if (once) {
        std::cout << fRotationAngle;
        once = false;
    }

#if 0
    // Clear background
    canvas->clear(SK_ColorWHITE);

    SkPaint paint;
    paint.setColor(SK_ColorRED);

    canvas->drawPoint(3, 5, paint);

    // Draw a rectangle with red paint
    SkRect rect = SkRect::MakeXYWH(10, 10, 128, 128);
    canvas->drawRect(rect, paint);

    // Set up a linear gradient and draw a circle
    {
        SkPoint linearPoints[] = { { 0, 0 }, { 300, 300 } };
        SkColor linearColors[] = { SK_ColorGREEN, SK_ColorBLACK };
        paint.setShader(SkGradientShader::MakeLinear(linearPoints, linearColors, nullptr, 2,
                                                     SkTileMode::kMirror));
        paint.setAntiAlias(true);

        canvas->drawCircle(200, 200, 64, paint);

        // Detach shader
        paint.setShader(nullptr);
    }

    // Draw a message with a nice black paint
    SkFont font;
    font.setSubpixel(true);
    font.setSize(20);
    paint.setColor(SK_ColorBLACK);

    canvas->save();
    static const char message[] = "Hello World";

    // Translate and rotate
    canvas->translate(300, 400);
    fRotationAngle += 0.2f;
    if (fRotationAngle > 360) {
        fRotationAngle -= 360;
    }
    canvas->rotate(fRotationAngle);

    // Draw the text
    canvas->drawSimpleText(message, strlen(message), SkTextEncoding::kUTF8, 0, 0, font, paint);

    canvas->restore();
#endif
}

void HelloWorldSoftware::onIdle() {
    // Just re-paint continously
    fWindow->inval();
}

bool HelloWorldSoftware::onChar(SkUnichar c, skui::ModifierKey modifiers) {
    if (' ' == c) {
        fBackendType = Window::kRaster_BackendType == fBackendType ? Window::kNativeGL_BackendType
                                                                   : Window::kRaster_BackendType;
        fWindow->detach();
        fWindow->attach(fBackendType);
    }
    return true;
}
