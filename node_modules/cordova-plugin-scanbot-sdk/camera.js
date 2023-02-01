"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
var __generator = (this && this.__generator) || function (thisArg, body) {
    var _ = { label: 0, sent: function() { if (t[0] & 1) throw t[1]; return t[1]; }, trys: [], ops: [] }, f, y, t, g;
    return g = { next: verb(0), "throw": verb(1), "return": verb(2) }, typeof Symbol === "function" && (g[Symbol.iterator] = function() { return this; }), g;
    function verb(n) { return function (v) { return step([n, v]); }; }
    function step(op) {
        if (f) throw new TypeError("Generator is already executing.");
        while (_) try {
            if (f = 1, y && (t = op[0] & 2 ? y["return"] : op[0] ? y["throw"] || ((t = y["return"]) && t.call(y), 0) : y.next) && !(t = t.call(y, op[1])).done) return t;
            if (y = 0, t) op = [op[0] & 2, t.value];
            switch (op[0]) {
                case 0: case 1: t = op; break;
                case 4: _.label++; return { value: op[1], done: false };
                case 5: _.label++; y = op[1]; op = [0]; continue;
                case 7: op = _.ops.pop(); _.trys.pop(); continue;
                default:
                    if (!(t = _.trys, t = t.length > 0 && t[t.length - 1]) && (op[0] === 6 || op[0] === 2)) { _ = 0; continue; }
                    if (op[0] === 3 && (!t || (op[1] > t[0] && op[1] < t[3]))) { _.label = op[1]; break; }
                    if (op[0] === 6 && _.label < t[1]) { _.label = t[1]; t = op; break; }
                    if (t && _.label < t[2]) { _.label = t[2]; _.ops.push(op); break; }
                    if (t[2]) _.ops.pop();
                    _.trys.pop(); continue;
            }
            op = body.call(thisArg, _);
        } catch (e) { op = [6, e]; y = 0; } finally { f = t = 0; }
        if (op[0] & 5) throw op[1]; return { value: op[0] ? op[1] : void 0, done: true };
    }
};
exports.__esModule = true;
var ScanbotHTMLFinderConfiguration = /** @class */ (function () {
    function ScanbotHTMLFinderConfiguration() {
    }
    return ScanbotHTMLFinderConfiguration;
}());
exports.ScanbotHTMLFinderConfiguration = ScanbotHTMLFinderConfiguration;
var ScanbotHTMLCamera = /** @class */ (function () {
    function ScanbotHTMLCamera() {
        this.isDetecting = false;
    }
    // @ts-ignore
    ScanbotHTMLCamera.prototype.initialize = function (container) {
        return __awaiter(this, void 0, void 0, function () {
            var constraints, stream;
            var _this = this;
            return __generator(this, function (_a) {
                switch (_a.label) {
                    case 0:
                        if (this.isiOS()) {
                            throw new Error('ScanbotSDK HTML5 Camera is an Android-only feature');
                        }
                        this.container = container;
                        this.video = document.createElement("video");
                        this.video.defaultMuted = true;
                        this.video.autoplay = true;
                        this.video.setAttribute("playsInline", "");
                        this.video.setAttribute("webkit-playsinline", "");
                        this.video.style.width = "100%";
                        this.video.style.height = "100%";
                        this.video.style.objectFit = "cover";
                        container.appendChild(this.video);
                        constraints = { video: { facingMode: "environment" } };
                        return [4 /*yield*/, navigator.mediaDevices.getUserMedia(constraints)];
                    case 1:
                        stream = _a.sent();
                        // @ts-ignore
                        return [4 /*yield*/, new Promise(function (resolve) {
                                _this.video.onloadedmetadata = resolve;
                                _this.video.srcObject = stream;
                                _this.video.width = container.offsetWidth;
                                _this.video.height = container.offsetHeight;
                            })];
                    case 2:
                        // @ts-ignore
                        _a.sent();
                        this.canvas = document.createElement('canvas');
                        this.canvas.width = this.video.videoWidth;
                        this.canvas.height = this.video.videoHeight;
                        this.canvas.style.display = 'none';
                        this.video.parentElement.appendChild(this.canvas);
                        this.canvasContext = this.canvas.getContext('2d');
                        return [2 /*return*/];
                }
            });
        });
    };
    ScanbotHTMLCamera.prototype.addViewFinder = function (configuration) {
        // Give video absolute position and size to draw viewfinder on top of it
        this.video.style.width = this.container.style.width;
        this.video.style.height = this.container.style.height;
        this.video.style.position = "absolute";
        this.viewFinderBackground = document.createElement('div');
        this.viewFinderBackground.className = "scanbot-camera-overlay";
        this.viewFinderBackground.style.backgroundColor = configuration.backgroundColor ? configuration.backgroundColor : "black";
        this.viewFinderBackground.style.opacity = "0.7";
        this.viewFinderBackground.style.position = "absolute";
        this.viewFinderBackground.style.width = this.video.width + "px";
        this.viewFinderBackground.style.height = this.video.height + "px";
        // @ts-ignore
        this.viewFinderBackground.style.mixBlendMode = "hard-light";
        this.container.appendChild(this.viewFinderBackground);
        var height = configuration.height ? configuration.height : this.video.height / 3 * 2;
        var width = configuration.width ? configuration.width : height;
        var x = configuration.marginLeft ? configuration.marginLeft : this.video.width / 2 - width / 2;
        var y = configuration.marginTop ? configuration.marginTop : this.video.height / 2 - height / 2;
        this.viewFinderHole = document.createElement('div');
        this.viewFinderHole.className = "scanbot-camera-viewfinder";
        this.viewFinderHole.style.width = width + "px";
        this.viewFinderHole.style.height = height + "px";
        this.viewFinderHole.style.marginLeft = x + "px";
        this.viewFinderHole.style.marginTop = y + "px";
        this.viewFinderHole.style.border = configuration.border ? configuration.border : "solid 2px white";
        // Check for undefined, because 0 is falsey, but it's an allowed value
        this.viewFinderHole.style.borderRadius = ((configuration.borderRadius !== undefined) ? configuration.borderRadius : 10) + "px";
        this.viewFinderHole.style.backgroundColor = "gray";
        this.viewFinderBackground.appendChild(this.viewFinderHole);
        return this.viewFinderHole;
    };
    /**
     * Public functions
     */
    ScanbotHTMLCamera.prototype.dispose = function () {
        if (!this.video) {
            return;
        }
        this.stopBarcodeDetector();
        this.video.pause();
        this.video.removeAttribute('src'); // empty source
        this.video.removeAttribute('playsInline');
        this.video.removeAttribute('webkit-playsinline');
        this.video.load();
        this.container.removeChild(this.video);
        this.container.removeChild(this.viewFinderBackground);
    };
    ScanbotHTMLCamera.prototype.startBarcodeDetector = function (formats, callback) {
        var _this = this;
        this.formats = formats;
        requestAnimationFrame(function (animCB) {
            _this.isDetecting = true;
            _this.sendImageData(callback).then(function (r) {
                // Nothing to resolve, carry on
            });
        });
    };
    ScanbotHTMLCamera.prototype.stopBarcodeDetector = function () {
        this.isDetecting = false;
    };
    /**
     * Static object creator
     */
    // @ts-ignore
    ScanbotHTMLCamera.create = function (container) {
        return __awaiter(this, void 0, void 0, function () {
            var camera;
            return __generator(this, function (_a) {
                switch (_a.label) {
                    case 0:
                        camera = new ScanbotHTMLCamera();
                        return [4 /*yield*/, camera.initialize(container)];
                    case 1:
                        _a.sent();
                        return [2 /*return*/, camera];
                }
            });
        });
    };
    /**
     * Internal private functions
     */
    ScanbotHTMLCamera.prototype.createImageData = function (canvasContext, imageOrVideoElement) {
        canvasContext.drawImage(imageOrVideoElement, 0, 0, this.video.videoWidth, this.video.videoHeight);
        var width = this.container.offsetWidth * 1.5;
        var height = this.container.offsetHeight * 1.5;
        var x = this.video.videoWidth / 2 - width / 2;
        var y = this.video.videoHeight / 2 - height / 2;
        if (this.viewFinderHole) {
            x += this.domPixelSizeToInt(this.viewFinderHole.style.marginLeft) * 1.5;
            y += this.domPixelSizeToInt(this.viewFinderHole.style.marginTop) * 1.5;
            width = this.domPixelSizeToInt(this.viewFinderHole.style.width) * 1.5;
            height = this.domPixelSizeToInt(this.viewFinderHole.style.height) * 1.5;
        }
        return canvasContext.getImageData(x, y, width, height);
    };
    ScanbotHTMLCamera.prototype.domPixelSizeToInt = function (size) {
        return parseInt(size.replace("px", ""), 10);
    };
    // @ts-ignore
    ScanbotHTMLCamera.prototype.sendImageData = function (result) {
        return __awaiter(this, void 0, void 0, function () {
            var data, imageData, octet;
            var _this = this;
            return __generator(this, function (_a) {
                switch (_a.label) {
                    case 0:
                        if (!this.isDetecting) {
                            return [2 /*return*/];
                        }
                        data = this.createImageData(this.canvasContext, this.video);
                        if (!this.isiOS()) return [3 /*break*/, 1];
                        imageData = data.data.buffer;
                        return [3 /*break*/, 3];
                    case 1: return [4 /*yield*/, this.Uint8ToStringViaReader(new Uint8Array(data.data))];
                    case 2:
                        octet = _a.sent();
                        imageData = octet;
                        _a.label = 3;
                    case 3:
                        // Uncomment for web debugging
                        // requestAnimationFrame(() => this.sendImageData(result));
                        // TODON'T: Do not follow the suggested Add 'import {cordova} from "@ionic-native/core"'
                        // The ionic core import is not correct, we want to use the "cordova native" function
                        // @ts-ignore
                        cordova.exec(function (success) { return __awaiter(_this, void 0, void 0, function () {
                            var _this = this;
                            return __generator(this, function (_a) {
                                requestAnimationFrame(function () { return _this.sendImageData(result); });
                                result(success);
                                return [2 /*return*/];
                            });
                        }); }, function (err) {
                            requestAnimationFrame(function () { return _this.sendImageData(result); });
                        }, "ScanbotSdk", "detectBarcodesFromBytes", [data.width, data.height, imageData, this.formats]);
                        return [2 /*return*/];
                }
            });
        });
    };
    ScanbotHTMLCamera.prototype.Uint8ToStringViaReader = function (u8a) {
        // @ts-ignore
        return new Promise(function (resolve) {
            var r = new FileReader();
            r.onload = function (ev) { resolve(r.result); };
            r.readAsBinaryString(new Blob([u8a], { type: "binary/octet-stream" }));
        });
    };
    ScanbotHTMLCamera.prototype.isiOS = function () {
        // @ts-ignore
        return /iPad|iPhone|iPod/.test(navigator.userAgent) && !window.MSStream;
    };
    return ScanbotHTMLCamera;
}());
exports["default"] = ScanbotHTMLCamera;
// @ts-ignore
module.exports = ScanbotHTMLCamera;
