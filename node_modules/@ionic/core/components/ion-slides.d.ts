import type { Components, JSX } from "../dist/types/components";

interface IonSlides extends Components.IonSlides, HTMLElement {}
export const IonSlides: {
  prototype: IonSlides;
  new (): IonSlides;
};
/**
 * Used to define this component and all nested components recursively.
 */
export const defineCustomElement: () => void;
