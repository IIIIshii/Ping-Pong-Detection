function [x, y, valid] = selectBall(centroid, area, perimeter, majorAxis)
    % selectBall  Blob Analysis の出力からボール候補を1つ選ぶ.
    %   ref.py の cv2.minEnclosingCircle + 半径/円形度フィルタ相当.
    %   Simulink の MATLAB Function ブロックに貼って使う.
    %
    %   入力 (Blob Analysis の上位 Centroid/Area/Perimeter/MajorAxisLength):
    %     centroid  : Nx2 (px) 各ブロブの重心
    %     area      : Nx1 (px^2)
    %     perimeter : Nx1 (px)
    %     majorAxis : Nx1 (px) 外接楕円の長軸 = 2*radius 相当
    %   出力:
    %     x, y      : single (px). 検出無効なら NaN
    %     valid     : boolean

    MIN_RADIUS  = 2;
    MAX_RADIUS  = 150;
    CIRC_THRESH = 0.7;

    x = single(NaN);
    y = single(NaN);
    valid = false;

    if isempty(area)
        return;
    end

    [~, idx] = max(area);
    a = double(area(idx));
    p = double(perimeter(idx));
    radius      = double(majorAxis(idx)) / 2;
    circularity = 4 * pi * a / (p^2 + 1e-6);

    if radius > MIN_RADIUS && radius < MAX_RADIUS && circularity > CIRC_THRESH
        x = single(centroid(idx, 1));
        y = single(centroid(idx, 2));
        valid = true;
    end
end
