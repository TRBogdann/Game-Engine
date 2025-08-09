#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec4 aColor;

uniform float iTime;
uniform float ar;

float sun(float x, float y) {
    x = x * 1.5 * 1.5;
    y = y * 1.5 * 1.5;
    float val = sin(10.0 * x + 1.5 + iTime * 5.0) +
            sin(15.0 * y + 2.1 + iTime * 5.0) +
            sin(25.0 * (x + y) + 0.7 + iTime * 5.0) +
            sin(40.0 * (x - y) + 1.2 + iTime * 5.0);
    val = val / 4.0;
    return (val + 1.0) / 2.0;
}

out vec4 ourColor;

void main() {
    vec2 uv = vec2(aPos.x, aPos.y);
    float xCol = uv.x * ar;
    float yCol = uv.y;
    if (xCol < 0.0)
        xCol = xCol * -1.0;
    if (yCol < 0.0)
        yCol = yCol * -1.0;
    float val = 1.0 - 0.6 * sqrt(xCol * xCol + yCol * yCol);
    vec3 col = vec3(val, val, val);
    float checkZ = 0.0;
    float tempX = cos(iTime / 2.0) * 4.0;
    float tempZ = sin(iTime / 2.0) * 2.0;
    //float th = (uv.x*ar-tempX)*(uv.x*ar-tempX)+(uv.y-tempY)*(uv.y-tempY);
    float th = (uv.x * ar) * (uv.x * ar) + (uv.y) * (uv.y);

    if (th < 0.25)
    {
        checkZ = 1.0;
        float sunCol = 0.5 + 0.5 * (1.0 - sun(uv.x, uv.y)) + 0.9;
        float gray = 0.5 + (th / 0.25) * 0.4;
        col = vec3(sunCol * gray, sunCol * 0.75 * gray, 0);
    }

    tempX = cos(iTime + 20.0);
    tempZ = sin(iTime + 20.0) / 2.0;
    float ratio = 2.0 - (tempZ / 2.0 + 0.5);
    float xVal = (uv.x * ar - tempX) / ratio;
    float yVal = uv.y / ratio;
    float th2 = xVal * xVal + yVal * yVal;
    if (th2 < 0.1 * 0.1)
    {
        float gray = 1.0 - th2 / 0.01;

        if (checkZ < 0.5 || ratio > 1.5)
        {
            if (ratio > 1.5)
            {
                gray = gray * 0.3;
            }
            else
            {
                gray = gray * (val + 0.4);
            }
            col = vec3(gray, 0, 0);
        }
        checkZ = 1.0;
    }

    tempX = cos(iTime * 0.8 + 10.0) * 2.0;
    tempZ = sin(iTime * 0.8 + 10.0);
    ratio = 2.0 - (tempZ / 2.0 + 0.5);
    xVal = (uv.x * ar - tempX) / ratio;
    yVal = uv.y / ratio;
    th2 = xVal * xVal + yVal * yVal;
    if (th2 < 0.2 * 0.2)
    {
        float gray = 1.0 - th2 / 0.04;

        if (checkZ < 0.5 || ratio > 1.5)
        {
            if (ratio > 1.5)
            {
                gray = gray * 0.3;
            }
            else
            {
                gray = gray * (val + 0.4);
            }
            col = vec3(0, gray, gray);
        }
        checkZ = 1.0;
    }

    tempX = cos(iTime / 2.0) * 4.0;
    tempZ = sin(iTime / 2.0) * 2.0;
    ratio = 2.0 - (tempZ / 2.0 + 0.5);
    xVal = (uv.x * ar - tempX) / ratio;
    yVal = uv.y / ratio;
    th2 = xVal * xVal + yVal * yVal;
    if (th2 < 0.2 * 0.2)
    {
        float gray = 1.0 - th2 / 0.04;

        if (checkZ < 0.5 || ratio > 1.5)
        {
            if (ratio > 1.5)
            {
                gray = gray * 0.3;
            }
            else
            {
                gray = gray * (val + 0.4);
            }
            col = vec3(gray, gray * 0.5, gray * 0.1);
        }
    }

    gl_Position = vec4(aPos, 1.0);
    ourColor = vec4(col, 1.0f);
}
