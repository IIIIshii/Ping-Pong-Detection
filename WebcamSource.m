classdef WebcamSource < matlab.System
    % WebcamSource  Simulink からUSBカメラを取得するための System object.
    %   MATLAB Support Package for USB Webcams (`webcam` 関数) を使う。
    %   Simulink 上では「MATLAB System」ブロックの System object name に
    %   `WebcamSource` を指定して使う。

    properties (Nontunable)
        DeviceIndex (1,1) double = 1
        Width       (1,1) double = 1280
        Height      (1,1) double = 720
        FrameRate   (1,1) double = 30
    end

    properties (Access = private)
        Cam
    end

    methods (Access = protected)
        function setupImpl(obj)
            obj.Cam = webcam(obj.DeviceIndex);
            try
                obj.Cam.Resolution = sprintf('%dx%d', obj.Width, obj.Height);
            catch
                % 解像度設定不可なカメラはデフォルトに任せる
            end
        end

        function img = stepImpl(obj)
            img = snapshot(obj.Cam);
        end

        function releaseImpl(obj)
            obj.Cam = [];
        end

        function sz = getOutputSizeImpl(obj)
            sz = [obj.Height, obj.Width, 3];
        end

        function dt = getOutputDataTypeImpl(~)
            dt = 'uint8';
        end

        function c = isOutputComplexImpl(~)
            c = false;
        end

        function f = isOutputFixedSizeImpl(~)
            f = true;
        end

        function st = getSampleTimeImpl(obj)
            st = matlab.system.SampleTimeSpecification( ...
                'Type', 'Discrete', ...
                'SampleTime', 1/obj.FrameRate);
        end
    end
end
