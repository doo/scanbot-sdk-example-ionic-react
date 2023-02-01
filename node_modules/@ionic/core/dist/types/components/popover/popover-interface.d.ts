import type { AnimationBuilder, ComponentProps, ComponentRef, FrameworkDelegate, Mode, OverlayInterface } from '../../interface';
export interface PopoverInterface extends OverlayInterface {
  present: (event?: MouseEvent | TouchEvent | PointerEvent) => Promise<void>;
}
export interface PopoverOptions<T extends ComponentRef = ComponentRef> {
  component: T;
  componentProps?: ComponentProps<T>;
  showBackdrop?: boolean;
  backdropDismiss?: boolean;
  translucent?: boolean;
  cssClass?: string | string[];
  event?: Event;
  delegate?: FrameworkDelegate;
  animated?: boolean;
  mode?: Mode;
  keyboardClose?: boolean;
  id?: string;
  htmlAttributes?: PopoverAttributes;
  enterAnimation?: AnimationBuilder;
  leaveAnimation?: AnimationBuilder;
  size?: PopoverSize;
  dismissOnSelect?: boolean;
  reference?: PositionReference;
  side?: PositionSide;
  alignment?: PositionAlign;
  arrow?: boolean;
  trigger?: string;
  triggerAction?: string;
}
/**
 * @deprecated - Use { [key: string]: any } directly instead.
 */
export declare type PopoverAttributes = {
  [key: string]: any;
};
export declare type PopoverSize = 'cover' | 'auto';
export declare type TriggerAction = 'click' | 'hover' | 'context-menu';
export declare type PositionReference = 'trigger' | 'event';
export declare type PositionSide = 'top' | 'right' | 'bottom' | 'left' | 'start' | 'end';
export declare type PositionAlign = 'start' | 'center' | 'end';
