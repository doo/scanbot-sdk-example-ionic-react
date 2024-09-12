import { useIonAlert } from "@ionic/react";

export const ShowAlert = async (title: string, message: string, actionButtons: Array<string>) => {

    const [presentAlert] = useIonAlert();

    await presentAlert({
        header: title,
        message: message,
        buttons: actionButtons,
    })
};