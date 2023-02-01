import { BarcodeFormat } from "./index";
export declare class ScanbotHTMLFinderConfiguration {
    /**
     * Background color of the finder overlay. 'gray' color is not allowed.
     * Defaults to black
     */
    backgroundColor?: string;
    /**
     * Border style of the finder view
     * Defaults to 'solid 2px white'
     */
    border?: string;
    /**
     * Corner radius of the finder view, in pixels.
     * Defaults to 10
     */
    borderRadius?: number;
    /**
     * Relative top margin of the finder frame, in pixels.
     * Size and position defaults to centered square 66% of the size of ScanbotHTMLCamera
     */
    marginTop?: number;
    /**
     * Relative left margin of the finder frame, in pixels.
     * Size and position defaults to centered square 66% of the size of ScanbotHTMLCamera
     */
    marginLeft?: number;
    /**
     * Relative width of the finder frame, in pixels.
     * Size and position defaults to centered square 66% of the size of ScanbotHTMLCamera
     */
    width?: number;
    /**
     * Relative height of the finder frame, in pixels.
     * Size and position defaults to centered square 66% of the size of ScanbotHTMLCamera
     */
    height?: number;
}
export default class ScanbotHTMLCamera {
    private container;
    private video;
    private canvasContext;
    private canvas;
    private viewFinderBackground;
    private viewFinderHole;
    isDetecting: boolean;
    initialize(container: HTMLElement): Promise<void>;
    addViewFinder(configuration: ScanbotHTMLFinderConfiguration): HTMLElement;
    private formats;
    /**
     * Public functions
     */
    dispose(): void;
    startBarcodeDetector(formats: BarcodeFormat[], callback: any): void;
    stopBarcodeDetector(): void;
    /**
     * Static object creator
     */
    static create(container: HTMLElement): Promise<ScanbotHTMLCamera>;
    /**
     * Internal private functions
     */
    private createImageData;
    private domPixelSizeToInt;
    private sendImageData;
    private Uint8ToStringViaReader;
    private isiOS;
}
