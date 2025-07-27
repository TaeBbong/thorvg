/*
 * Copyright (c) 2023 - 2025 the ThorVG project. All rights reserved.

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "Example.h"

/************************************************************************/
/* ThorVG Drawing Contents                                              */
/************************************************************************/

struct UserExample : tvgexam::Example
{
    bool content(tvg::Canvas* canvas, uint32_t w, uint32_t h) override
    {
        // Size Variables
        float sx = w * 0.6f;
        float sy = h * 0.6f;
        float cx = w * 0.5f;
        float cy = h * 0.5f;
        float left = cx - sx * 0.5f;
        float top = cy - sy * 0.5f;
        float radius = std::min(sx, sy) * 0.18f;

        // Background
        auto bg = tvg::Shape::gen();
        bg->appendRect(0, 0, w, h);
        bg->fill(100, 100, 100);
        canvas->push(bg);

        // Rounded Square
        auto square = tvg::Shape::gen();
        square->appendRect(left, top, sx, sy, radius, radius);
        square->strokeWidth(std::min(sx, sy) * 0.07f);
        square->strokeFill(255, 255, 255);

        // Gradient
        // Color referenced by https://www.color-hex.com/color-palette/44340
        auto grad = tvg::LinearGradient::gen();
        grad->linear(left, top, left + sx, top + sy);

        tvg::Fill::ColorStop colorStops[5];
        colorStops[0] = {0, 254, 218, 117, 255}; // yellow
        colorStops[1] = {0.25, 250, 126, 30, 255}; // orange
        colorStops[2] = {0.5, 214, 41, 118, 255}; // magenta
        colorStops[3] = {0.75, 150, 47, 191, 255}; // purple
        colorStops[4] = {1, 79, 91, 213, 255}; // indigo
        
        grad->colorStops(colorStops, 5);
        square->fill(grad);

        canvas->push(square);

        // Center Circle
        auto circle = tvg::Shape::gen();
        circle->appendCircle(cx, cy, sx * 0.26f, sy * 0.26f);
        circle->fill(0, 0, 0, 0);
        circle->strokeWidth(std::min(sx, sy) * 0.07f);
        circle->strokeFill(255, 255, 255);
        canvas->push(circle);

        // Top‑right Dot
        auto dot = tvg::Shape::gen();
        dot->appendCircle(cx + sx * 0.26f, cy - sy * 0.26f, sx * 0.05f, sy * 0.05f);
        dot->fill(255, 255, 255, 255);
        canvas->push(dot);

        return true;
    }
};

/************************************************************************/
/* Entry Point                                                          */
/************************************************************************/

int main(int argc, char **argv)
{
    return tvgexam::main(new UserExample, argc, argv, false, 1024, 1024, 4, true);
}