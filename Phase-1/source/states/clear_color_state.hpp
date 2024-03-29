#pragma once

#include <application.hpp>

class ClearColorState: public our::State {
    // onInitialize() function is called once before the state starts
    void onInitialize() override {
        //TODO: Read the color from the configuration file and use it to set the clear color for the window
        //HINT: you can the configuration for the whole application using "getApp()->getConfig()"
        //To see how the clear color is written in the json files, see "config/blue-screen.json"
        //To know how read data from a nlohmann::json object, 
        //look at the following documentation: https://json.nlohmann.me/features/element_access/

        // ================ < --- Clear Window Color --- > ================ //

        //==// Access App.json -> Scene -> Clear Colors.
        auto color = getApp()->getConfig().at("scene").at("clear-color");

        //==// Read Every Color Chanel Value & Read Alpha
        float red = color.at("r").get<float>();
        float green = color.at("g").get<float>();
        float blue = color.at("b").get<float>();
        float alpha = color.at("a").get<float>();

        //==// Set The Color values for the color buffer in GPU.
        glClearColor(red, green, blue, alpha);

        //==// Clears Window with Color That Stored In buffer.
        glClear(GL_COLOR_BUFFER_BIT);

        // ================ < --- End --- > ================ //

    }

    // onDraw(deltaTime) function is called every frame 
    void onDraw(double deltaTime) override {
        //At the start of frame we want to clear the screen. Otherwise we would still see the results from the previous frame.
        glClear(GL_COLOR_BUFFER_BIT);
    }
};