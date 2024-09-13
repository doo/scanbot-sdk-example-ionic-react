import { IonButton, IonContent, IonHeader, IonItem, IonLabel, IonList, IonModal, IonTitle, IonToolbar } from "@ionic/react";
import { useRef } from "react";

type Props = {
    id: string,
    modalTitle: string,
    buttonTitle: string,
    initialBreakPoint: number,
    optionList: { key: any; value: string; }[],
    onItemClick: Function
};

const CommonModalView: React.FC<Props> = (props: Props) => {

    const modal = useRef<HTMLIonModalElement>(null);

    async function dismiss() {
        await modal.current?.dismiss();
    }

    return (
        <>
            <IonButton id={props.id} expand="block">
                {props.buttonTitle}
            </IonButton>

            <IonModal ref={modal} trigger={props.id} initialBreakpoint={props.initialBreakPoint} breakpoints={[0, 0.25, 0.5, 0.75, 1]}>
                <IonHeader>
                    <IonToolbar>
                        <IonTitle>{props.modalTitle}</IonTitle>
                        <IonLabel className='ion-padding' slot="end" onClick={dismiss}>
                            Cancel
                        </IonLabel>
                    </IonToolbar>
                </IonHeader>
                <IonContent className="ion-padding">
                    <IonList>
                        {
                            props.optionList.map((item) => (
                                <IonItem button key={item.key} onClick={() => props.onItemClick(item.key)}>
                                    <IonLabel>{item.value}</IonLabel>
                                </IonItem>
                            ))
                        }
                    </IonList>
                </IonContent>
            </IonModal>
        </>
    );
}

export default CommonModalView;