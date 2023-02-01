import type { Components, JSX } from "../dist/types/components";

interface IonSlide extends Components.IonSlide, HTMLElement {}
export const IonSlide: {
  prototype: IonSlide;
  new (): IonSlide;
};
/**
 * Used to define this component and all nested components recursively.
 */
export const defineCustomElement: () => void;
