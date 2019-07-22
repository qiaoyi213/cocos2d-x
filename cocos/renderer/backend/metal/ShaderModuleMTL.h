/****************************************************************************
 Copyright (c) 2018-2019 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
 
#pragma once

#include "../ShaderModule.h"
#include "../Types.h"

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#import <Metal/Metal.h>

struct glslopt_shader;

CC_BACKEND_BEGIN
/**
 * @addtogroup _metal
 * @{
 */

/**
 * To Create a vertex or fragment shader.
 */
class ShaderModuleMTL : public ShaderModule
{
public:
    /**
     * @param mtlDevice The device for which MTLFunction object was created.
     * @param stage Specify what kinds of shader to be created.
     * @param source Specify the shader source.
     */
    ShaderModuleMTL(id<MTLDevice> mtlDevice, ShaderStage stage, const std::string& source);
    ~ShaderModuleMTL();
    
    /**
     * Get MTLFunction object.
     * @return A MTLFunction object.
     */
    inline id<MTLFunction> getMTLFunction() const { return _mtlFunction; }
    
    /**
     * Get current shader uniform informatino.
     * @return Uniform information. Key is each uniform name, Value is corresponding uniform info.
     */
    inline const std::unordered_map<std::string, UniformInfo>& getUniforms() const { return _uniformInfos; }
    
    /**
     * Get maximum uniform location.
     * @return Maximum uniform location.
     */
    inline const int getMaxLocation() const { return _maxLocation; }
    
    /**
     * Get active attribute informations.
     * @return Active attribute informations. key is attribute name and Value is corresponding attribute info.
     */
    inline const std::unordered_map<std::string, AttributeBindInfo> getAttributeInfo() const { return _attributeInfo; }
    
private:
    void parseAttibute(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    void parseUniform(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    void parseTexture(id<MTLDevice> mtlDevice, glslopt_shader* shader);
    
    id<MTLFunction> _mtlFunction = nil;
    
    std::unordered_map<std::string, UniformInfo> _uniformInfos;
    std::unordered_map<std::string, AttributeBindInfo> _attributeInfo;
    
    int _maxLocation = -1;
};

// end of _metal group
/// @}
CC_BACKEND_END