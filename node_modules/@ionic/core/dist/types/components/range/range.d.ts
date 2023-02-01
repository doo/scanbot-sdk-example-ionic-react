import type { ComponentInterface, EventEmitter } from '../../stencil-public-runtime';
import type { Color, RangeChangeEventDetail, RangeKnobMoveEndEventDetail, RangeKnobMoveStartEventDetail, RangeValue, StyleEventDetail } from '../../interface';
import type { PinFormatter } from './range-interface';
/**
 * @virtualProp {"ios" | "md"} mode - The mode determines which platform styles to use.
 *
 * @slot start - Content is placed to the left of the range slider in LTR, and to the right in RTL.
 * @slot end - Content is placed to the right of the range slider in LTR, and to the left in RTL.
 *
 * @part tick - An inactive tick mark.
 * @part tick-active - An active tick mark.
 * @part pin - The counter that appears above a knob.
 * @part knob - The handle that is used to drag the range.
 * @part bar - The inactive part of the bar.
 * @part bar-active - The active part of the bar.
 */
export declare class Range implements ComponentInterface {
  private rangeId?;
  private didLoad;
  private noUpdate;
  private rect;
  private hasFocus;
  private rangeSlider?;
  private gesture?;
  private inheritedAttributes;
  private contentEl;
  private initialContentScrollY;
  el: HTMLIonRangeElement;
  private ratioA;
  private ratioB;
  private pressedKnob;
  /**
   * The color to use from your application's color palette.
   * Default options are: `"primary"`, `"secondary"`, `"tertiary"`, `"success"`, `"warning"`, `"danger"`, `"light"`, `"medium"`, and `"dark"`.
   * For more information on colors, see [theming](/docs/theming/basics).
   */
  color?: Color;
  /**
   * How long, in milliseconds, to wait to trigger the
   * `ionChange` event after each change in the range value.
   * This also impacts form bindings such as `ngModel` or `v-model`.
   */
  debounce: number;
  protected debounceChanged(): void;
  /**
   * The name of the control, which is submitted with the form data.
   */
  name: string;
  /**
   * Show two knobs.
   */
  dualKnobs: boolean;
  /**
   * Minimum integer value of the range.
   */
  min: number;
  protected minChanged(): void;
  /**
   * Maximum integer value of the range.
   */
  max: number;
  protected maxChanged(): void;
  /**
   * If `true`, a pin with integer value is shown when the knob
   * is pressed.
   */
  pin: boolean;
  /**
   * A callback used to format the pin text.
   * By default the pin text is set to `Math.round(value)`.
   */
  pinFormatter: PinFormatter;
  /**
   * If `true`, the knob snaps to tick marks evenly spaced based
   * on the step property value.
   */
  snaps: boolean;
  /**
   * Specifies the value granularity.
   */
  step: number;
  /**
   * If `true`, tick marks are displayed based on the step value.
   * Only applies when `snaps` is `true`.
   */
  ticks: boolean;
  /**
   * The start position of the range active bar. This feature is only available with a single knob (dualKnobs="false").
   * Valid values are greater than or equal to the min value and less than or equal to the max value.
   */
  activeBarStart?: number;
  protected activeBarStartChanged(): void;
  /**
   * If `true`, the user cannot interact with the range.
   */
  disabled: boolean;
  protected disabledChanged(): void;
  /**
   * the value of the range.
   */
  value: RangeValue;
  protected valueChanged(value: RangeValue): void;
  private clampBounds;
  private ensureValueInBounds;
  /**
   * Emitted when the value property has changed.
   */
  ionChange: EventEmitter<RangeChangeEventDetail>;
  /**
   * Emitted when the styles change.
   * @internal
   */
  ionStyle: EventEmitter<StyleEventDetail>;
  /**
   * Emitted when the range has focus.
   */
  ionFocus: EventEmitter<void>;
  /**
   * Emitted when the range loses focus.
   */
  ionBlur: EventEmitter<void>;
  /**
   * Emitted when the user starts moving the range knob, whether through
   * mouse drag, touch gesture, or keyboard interaction.
   */
  ionKnobMoveStart: EventEmitter<RangeKnobMoveStartEventDetail>;
  /**
   * Emitted when the user finishes moving the range knob, whether through
   * mouse drag, touch gesture, or keyboard interaction.
   */
  ionKnobMoveEnd: EventEmitter<RangeKnobMoveEndEventDetail>;
  private setupGesture;
  componentWillLoad(): void;
  componentDidLoad(): void;
  connectedCallback(): void;
  disconnectedCallback(): void;
  private handleKeyboard;
  private getValue;
  private emitStyle;
  private onStart;
  private onMove;
  private onEnd;
  private update;
  private get valA();
  private get valB();
  private get ratioLower();
  private get ratioUpper();
  private updateRatio;
  private updateValue;
  private setFocus;
  private onBlur;
  private onFocus;
  render(): any;
}
